/* Elementary USB driver */

#define pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#include <linux/module.h>
#include <linux/usb.h>

#include "my_usb.h"

static int my_usb_probe(struct usb_interface *iface, const struct usb_device_id *id)
{
	pr_info("USB stick plugged in %04X:%04X\n", id->idVendor, id->idProduct);
	return 0;
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
MODULE_DESCRIPTION("USB device driver!");



