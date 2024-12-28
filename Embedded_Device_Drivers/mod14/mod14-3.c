/* USB client driver - read/write */

#define pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#include <linux/module.h>
#include <linux/usb.h>

#include "my_usb.h"

#define MIN(a,b)		((a)<(b)?(a):(b))

#define BULK_EP_OUT	0x81
#define BULK_EP_IN	0x02
#define MAX_PKT_SZ	(512)
#define TIMEOUT		(5000)		// 5 secs

static struct usb_device *device;
static struct usb_class_driver class;
static char data_buf[MAX_PKT_SZ] = {0};

static int my_usb_open(struct inode *inode, struct file *file)
{
	pr_info("%s called, device opened\n", __func__);
	return 0;
}

static int my_usb_close(struct inode *inode, struct file *file)
{
	pr_info("%s called, device closed\n", __func__);
	return 0;
}

static ssize_t my_usb_read(struct file *file, char __user *buf, size_t count, loff_t *pos)
{
	int ret;
	int nread;

	ret = usb_bulk_msg(device, usb_rcvbulkpipe(device, BULK_EP_IN), data_buf, MAX_PKT_SZ, &nread, TIMEOUT);
	if (ret)
	{
		pr_err("Error in usb_bulk_msg - recv:%d\n", ret);
		return ret;
	}

	if (copy_to_user(buf, data_buf, MIN(count, nread)))
	{
		return -EFAULT;
	}

	return MIN(count, nread);
}

static ssize_t my_usb_write(struct file *file, const char __user *buf, size_t count, loff_t *pos)
{
	int ret;
	int nwrite = MIN(count, MAX_PKT_SZ);

	if (copy_from_user(data_buf, buf, MIN(count, MAX_PKT_SZ)))
	{
		return -EFAULT;
	}

	pr_info("data_buf = %s\n", data_buf);

	ret = usb_bulk_msg(device, usb_sndbulkpipe(device, BULK_EP_OUT), data_buf, MIN(count, MAX_PKT_SZ), &nwrite, TIMEOUT);
	if (ret)
	{
		pr_err("Error in usb_bulk_msg - send:%d\n", ret);
		return ret;
	}

	return nwrite;
}

static struct file_operations my_usb_fops = 
{
	.open = my_usb_open,
	.release = my_usb_close,
	.read = my_usb_read,
	.write = my_usb_write
};

static int my_usb_probe(struct usb_interface *iface, const struct usb_device_id *id)
{
	int ret;

	pr_info("USB stick plugged in %04X:%04X\n", id->idVendor, id->idProduct);

	device = interface_to_usbdev(iface);

	class.name = "usb/my_usb_dev0";
	class.fops = &my_usb_fops;
	ret = usb_register_dev(iface, &class);
	if (ret<0)
	{
		pr_err("Unable to register %s\n", class.name);
	}
	else
		pr_info("%s registered with minor %d\n", class.name, iface->minor);

	return ret;
}

static void my_usb_disconnect(struct usb_interface *iface)
{
	pr_info("Device removed\n");
}

static struct usb_device_id my_usb_table[] =
{
	{USB_DEVICE(MY_USB_VENDOR,MY_USB_PRODUCT)},
	{}
};
MODULE_DEVICE_TABLE(usb, my_usb_table);

static struct usb_driver my_usb_driver =
{
	.name = "my_usb_driver",
	.id_table = my_usb_table,
	.probe = my_usb_probe,
	.disconnect = my_usb_disconnect
};

static int __init my_init(void)
{
	return usb_register(&my_usb_driver);
}

static void __exit my_exit(void)
{
	usb_deregister(&my_usb_driver);
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("CDAC EDD <edd@cdac.gov.in>");
MODULE_DESCRIPTION("USB device driver with read/write!");



