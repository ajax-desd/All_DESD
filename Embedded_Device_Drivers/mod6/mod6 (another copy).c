/* IOCTL on char device */

#define pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/err.h>
#include <linux/device.h>
#include <linux/kdev_t.h>
#include <linux/cdev.h>
#include <linux/ioctl.h>

#include "my_ioctls.h"

#define MY_CLASS_NAME	"cdac_cls"
#define MY_DEV_NAME	"cdac_dev"

// internal kernel variable - used for ioctl
static unsigned int value;

dev_t dev = 0;
static struct class *dev_class;
static struct device *cdevice;
static struct cdev my_cdev;

// function prototypes
static int __init my_mod_init(void);
static int my_open(struct inode *inode, struct file *file);
static ssize_t my_read(struct file *file, char __user *buf, size_t len, loff_t *off);
static ssize_t my_write(struct file *file, const char __user *buf, size_t len, loff_t *off);
static long my_ioctl(struct file *file, unsigned int cmd, unsigned long args);
static int my_release(struct inode *inode, struct file *file);
static void __exit my_mod_exit(void);

static int my_open(struct inode *inode, struct file *file)
{
	pr_info("My open function %s called\n", __func__);
	return 0;
}

static ssize_t my_read(struct file *file, char __user *buf, size_t len, loff_t *off)
{
	pr_info("My read function %s called\n", __func__);
	return 0;
}

static ssize_t my_write(struct file *file, const char __user *buf, size_t len, loff_t *off)
{
	pr_info("My write function %s called\n", __func__);
	return len;
}

static long my_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	switch(cmd)
	{
		case MY_HW_READ:
			if ( copy_to_user((unsigned int *)arg, &value, sizeof(value)) )
			{
				pr_err("Error reading from kernel variable\n");
			}
			pr_info("Kernel variable read, value = %d\n", value);
			break;
		case MY_HW_WRITE:
			if ( copy_from_user(&value, (unsigned int *)arg, sizeof(value)) )
			{
				pr_err("Error writing to kernel variable\n");
			}
			pr_info("Wrote %d to kernel variable\n", value);
			break;
		default:
			pr_err("Undefined command!\n");
			break;
	}
	return 0;
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
	.unlocked_ioctl = my_ioctl,
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
	pr_info("Goodbye world from %s!\n", KBUILD_MODNAME);
	device_destroy(dev_class, dev);
	class_destroy(dev_class);
	cdev_del(&my_cdev);
	unregister_chrdev_region(dev, 1);
	pr_info("major:minor numbers freed up...\n");
	return;
}

module_init(my_mod_init);
module_exit(my_mod_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("EDD <edd@cdac.gov.in>");
MODULE_DESCRIPTION("IOCTL on char device!");
