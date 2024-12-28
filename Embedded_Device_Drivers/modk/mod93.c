/* Kernel linked list - dynamic nodes, node replacement */

#define pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/list.h>

#include <linux/fs.h>
#include <linux/err.h>
#include <linux/device.h>
#include <linux/kdev_t.h>
#include <linux/cdev.h>
#include <linux/ioctl.h>
#include <linux/uaccess.h> // For copy_from_user
// number of nodes in the kernel linked list


// linked list node definition
struct my_node
{
	uint32_t  data;
	struct list_head my_list;
};

struct my_node *node;
LIST_HEAD(my_head);
#define MY_CLASS_NAME	"cdac_cls"
#define MY_DEV_NAME	"cdac_dev"

// internal kernel variable - used for ioctl


int count,w=0;
struct my_node  *tmp;
dev_t dev = 0;
static struct class *dev_class;
static struct device *cdevice;
static struct cdev my_cdev;

// function prototypes
static int __init my_mod_init(void);
static int my_open(struct inode *inode, struct file *file);
static ssize_t my_read(struct file *file, char __user *buf, size_t len, loff_t *off);
static ssize_t my_write(struct file *file, const char __user *buf, size_t len, loff_t *off);
static int my_release(struct inode *inode, struct file *file);
static void __exit my_mod_exit(void);


static int my_open(struct inode *inode, struct file *file)
{
	pr_info("My open function %s called\n", __func__);
	return 0;
}

/*static ssize_t my_read(struct file *file, char __user *buf, size_t len, loff_t *off)
{
	uint32_t data;
	pr_info("My read function %s called\n", __func__);
	
	if (copy_to_user(buf, &w, sizeof(uint32_t)))
		{
				pr_err("Error writing to kernel variable\n");
				return -1;
		}
	else{
	     buf += sizeof(uint32_t);
	}
	list_for_each_entry(tmp, &my_head, my_list)
	{
		data = tmp->data;
		if (copy_to_user(buf, &data, sizeof(uint32_t)) )
		{
				pr_err("Error writing to kernel variable\n");
				return -1;
		}
		 buf += sizeof(uint32_t);
	}
	
	
	return 0;
}
static ssize_t my_read(struct file *file, char __user *buf, size_t len, loff_t *off)
{
	pr_info("My read function %s called\n", __func__);
	if ( copy_to_user(buf, kbuf + *off, len) )
	{
		pr_err("Error in data write to userspace!\n");
	}
	pr_info("Data written to userspace\n");
	
	return len;
}*/


static ssize_t my_write(struct file *file, const char __user *buf, size_t len, loff_t *off)
{
	
	uint32_t data;
	node = (struct my_node *)kmalloc(sizeof(struct my_node), GFP_KERNEL);
	pr_info("My write function %s called\n", __func__);
	if (copy_from_user(&data, buf, sizeof(uint32_t)) )
	{
				pr_err("Error writing to kernel variable\n");
				return -1;
	}
	
	node->data =data;
	pr_info("%d\n",node->data);
	INIT_LIST_HEAD(&node->my_list);
	list_add(&node->my_list, &my_head);
	w++;
	return len;
}
static ssize_t my_read(struct file *file, char __user *buf, size_t len, loff_t *off)
{
    uint32_t data;
    size_t bytes_copied = 0;
    pr_info("My read function %s called\n", __func__);

   
    if (len < sizeof(uint32_t)) {
        pr_err("User buffer is too small to write data\n");
        return -EINVAL;  // Return invalid argument error
    }

  
    if (bytes_copied + sizeof(uint32_t) <= len) {
        if (copy_to_user(buf + bytes_copied, &w, sizeof(uint32_t))) {
            pr_err("Error writing initial kernel variable\n");
            return -EFAULT;  // Return error if copying fails
        }
        bytes_copied += sizeof(uint32_t);
    }

    
    list_for_each_entry(tmp, &my_head, my_list) {
        if (bytes_copied + sizeof(uint32_t) > len) {
            pr_warn("User buffer is full, stopping read\n");
            break;
        }

        data = tmp->data;
        pr_info("store num :: data=%d\n", data);

        if (copy_to_user(buf + bytes_copied, &data, sizeof(uint32_t))) {
            pr_err("Error writing to kernel variable\n");
            return -EFAULT; 
        }

        bytes_copied += sizeof(uint32_t);
    }

    *off += bytes_copied;
    pr_info("Data written to userspace, bytes copied: %zu\n", bytes_copied);

    return bytes_copied; 

        
/*
static ssize_t my_read(struct file *file, char __user *buf, size_t len, loff_t *off)
{
    uint32_t data;
    size_t bytes_copied = 0;
    pr_info("My read function %s called\n", __func__);

    
    if (len < sizeof(uint32_t)) {
        pr_err("User buffer is too small to write data\n");
        return -EINVAL;  
    }

     // First, check if there's space for 'w' (if needed)
    if (bytes_copied + sizeof(uint32_t) <= len) {
        if (copy_to_user(buf + bytes_copied, &w, sizeof(uint32_t))) {
            pr_err("Error writing to kernel variable\n");
            return -EFAULT;  // Return error if copying fails
        }
        bytes_copied += sizeof(uint32_t);
    }

   
    list_for_each_entry(tmp, &my_head, my_list) {
        data = tmp->data;
        pr_info("store num :: data=%d\n",data);

        if (copy_to_user(buf + bytes_copied, &data, sizeof(uint32_t))) {
            pr_err("Error writing to kernel variable\n");
            return -EFAULT;  // Return error if copying fails
        }
        

        bytes_copied += sizeof(uint32_t);
    }

   
    *off += bytes_copied;

    pr_info("Data written to userspace, bytes copied: %zu\n", bytes_copied);

    return bytes_copied;  // Return the number of bytes copied to user space
}

*/


static int my_release(struct inode *inode, struct file *file)
{
	pr_info("My release function %s called\n", __func__);
	
	pr_info("%d\n",w);
	return 0;
}

// create a fops struct
static struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = my_open,
	.read = my_read,
	.write = my_write,
	.release = my_release,
};

static int __init my_mod_init(void)
{
	
	
	//struct my_node *t;
	int ans;

	pr_info("Hello world from %s!\n", KBUILD_MODNAME);
	ans = alloc_chrdev_region(&dev, 0, 1, MY_DEV_NAME);
	if (ans<0)
	{
		pr_err("Error in major:minor allotment!\n");
		return -1;
	}
	pr_info("major:minor %d:%d allotted!\n", MAJOR(dev),MINOR(dev));

	// initialize a cdev
	cdev_init(&my_cdev, &fops);

	ans = cdev_add(&my_cdev, dev, 1);
	if (ans<0)
	{
		pr_err("Could not add cdev to the kernel!\n");
		goto r_cdev;
	}
	dev_class = class_create(THIS_MODULE, MY_CLASS_NAME);
	if (IS_ERR(dev_class))
	{
		pr_err("Could not create device class %s\n", MY_CLASS_NAME);
		goto r_class;
	}

	cdevice = device_create(dev_class, NULL, dev, NULL, MY_DEV_NAME);
	if (IS_ERR(cdevice))
	{
		pr_err("Could not create device %s\n", MY_DEV_NAME);
		goto r_device;
	}
	pr_info("Device %s under class %s created with success\n", 
			MY_DEV_NAME, MY_CLASS_NAME);

	
	
	return 0;
	
r_device:
        class_destroy(dev_class);
r_class:
        cdev_del(&my_cdev);
r_cdev:
        unregister_chrdev_region(dev, 1);
	return -1;
	
}

static void __exit my_mod_exit(void)
{	
	count  = 0;
	//struct my_node *node, *tmp;
	list_for_each_entry(tmp, &my_head, my_list)
	{
		pr_info("store num :: Node %d, data=%d\n", count++, tmp->data);
	}
	
	
	list_for_each_entry_safe(node, tmp, &my_head, my_list)
	{	
		pr_info("Deleting node with data=%d\n", node->data);
		list_del(&node->my_list);
		kfree(node);
	}
	
	device_destroy(dev_class, dev);
	class_destroy(dev_class);
	cdev_del(&my_cdev);
	unregister_chrdev_region(dev, 1);
	pr_info("major:minor numbers freed up...\n");
	
	pr_info("Goodbye world from %s!\n", KBUILD_MODNAME);

	return;
}

module_init(my_mod_init);
module_exit(my_mod_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("EDD <edd@cdac.gov.in>");
MODULE_DESCRIPTION("Kernel linked list - dynamic nodes, node replacement!");
