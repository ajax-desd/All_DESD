/* Demonstrating a completion for kthread */

#define pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/err.h>
#include <linux/device.h>
#include <linux/kdev_t.h>
#include <linux/cdev.h>

#include <linux/kthread.h>
#include <linux/completion.h>

#define MY_CLASS_NAME	"cdac_cls"
#define MY_DEV_NAME	"cdac_dev"

dev_t dev = 0;
static struct class *dev_class;
static struct device *cdevice;
static struct cdev my_cdev;

// wait thread related
static struct task_struct *wait_thread;
static char thread_name[] = "Wait-thread";

#define COMPLETION_READ		(1)
#define COMPLETION_EXIT		(2)
#define COMPLETION_WRITE	(3)
static int completion_flag; 		// either COMPLETION_READ or COMPLETION_EXIT

// completion variable
// indicates: either read is done, or it is time to self-exit
static struct completion read_done;

// function prototypes
static int __init my_mod_init(void);
static int my_open(struct inode *inode, struct file *file);
static ssize_t my_read(struct file *file, char __user *buf, size_t len, loff_t *off);
static ssize_t my_write(struct file *file, const char __user *buf, size_t len, loff_t *off);
static int my_release(struct inode *inode, struct file *file);
static void __exit my_mod_exit(void);

static int wait_func(void *pv)
{
	while(1)
	{
		pr_info("%s: Waiting...\n", __func__);
		wait_for_completion(&read_done);
		if (completion_flag == COMPLETION_EXIT)
		{
			pr_info("%s: Message from exit: self-exiting!\n", __func__);
			do_exit(0);
			
		}
		if(completion_flag == COMPLETION_READ){
			pr_info("%s: Message from read\n", __func__);
			break;
		}
		if(completion_flag == COMPLETION_WRITE){
			pr_info("%s: Message from read\n", __func__);
			break;
		}
		completion_flag = 0;
		
	}
	do_exit(0);
	return 0;
}

static int my_open(struct inode *inode, struct file *file)
{
	pr_info("My open function %s called\n", __func__);
	return 0;
}

static ssize_t my_read(struct file *file, char __user *buf, size_t len, loff_t *off)
{
	pr_info("My read function %s called\n", __func__);
	completion_flag = COMPLETION_READ;
	pr_info("Sent read done message!\n");
	if (!completion_done(&read_done))
	{
		complete(&read_done);
	}
	return 0;
}

static ssize_t my_write(struct file *file, const char __user *buf, size_t len, loff_t *off)
{
	pr_info("My write function %s called\n", __func__);
	completion_flag=COMPLETION_WRITE;
	pr_info("writing of mssg  done !\n");
	if (!completion_done(&read_done))
	{
		complete(&read_done);
	}
	return len;
}

static int my_release(struct inode *inode, struct file *file)
{
	pr_info("My release function %s called\n", __func__);
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

	init_completion(&read_done);
	pr_info("Completion initialized!\n");

	wait_thread = kthread_run(wait_func, NULL, thread_name);
	if (wait_thread)
	{
		pr_info("%s created and started\n", thread_name);
	}
	else
	{
		pr_err("Could not create %s\n", thread_name);
		goto r_wait_thread;
	}

	return 0;

r_wait_thread:
	device_destroy(dev_class, dev);
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
	completion_flag = COMPLETION_EXIT;
	pr_info("Sent exit message!\n");
	if (!completion_done(&read_done))
	{
		complete(&read_done);
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
MODULE_DESCRIPTION("Module demonstrating a completion for a kthread");
