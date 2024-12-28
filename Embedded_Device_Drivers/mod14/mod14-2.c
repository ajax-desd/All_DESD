/* USB stick probing example */

#define pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/usb.h>

#include "my_usb.h"	// get Vendor and Product

static int my_usb_probe (struct usb_interface *interface, const struct usb_device_id *id)
{
  struct usb_device *device;
  struct usb_device_descriptor *dev_desc;
  struct usb_config_descriptor *cfg_desc;
  struct usb_host_interface *iface_desc;
  struct usb_endpoint_descriptor *endpoint;
  int i;
  char *power_str;

  // device descriptor
  device = interface_to_usbdev (interface);
  pr_info("device: devnum=%d, devpath=%s, rx_lanes=%d, tx_lanes=%d\n", 
		  device->devnum, device->devpath,
		  device->rx_lanes, device->tx_lanes);
  pr_info("Device: product: %s, mfr: %s, serial=%s\n",
		  device->product, device->manufacturer, device->serial);
  pr_info("Device: speed: %d, state: %d\n", device->speed, device->state);

  dev_desc = &device->descriptor;
  pr_info("dev_desc: idVendor=0x%04X, idProduct=0x%04X\n", 
		  dev_desc->idVendor, dev_desc->idProduct);
  pr_info("dev_desc: bNumConfigurations=%d\n", 
		  dev_desc->bNumConfigurations);
  pr_info("----------------------------------------------------------------\n");

  // config descriptor
  cfg_desc = &device->config->desc;
  pr_info("cfg_desc: bNumInterfaces=%d, bMaxPower=%d mA\n",
		  cfg_desc->bNumInterfaces, cfg_desc->bMaxPower*2);
  i = cfg_desc->bmAttributes;
  if (i&0x80)
	  power_str = "Bus-powered";
  else if (i&0x40)
	  power_str = "Self-powered";
  else if (i&0x20)
	  power_str = "Remote-wakeup";
  else
	  power_str = "Reserved";
  pr_info("cfg_desc: bmAttributes=%02X %s\n",
		  cfg_desc->bmAttributes, power_str);

  pr_info("----------------------------------------------------------------\n");

  // interface descriptor
  iface_desc = interface->cur_altsetting;
  pr_info("Interface %d probed\n", iface_desc->desc.bInterfaceNumber);
  pr_info("bInterfaceclass: %02d, bInterfaceSubClass: %02d, bInterfaceProtocol: %02d\n", iface_desc->desc.bInterfaceClass, iface_desc->desc.bInterfaceSubClass, iface_desc->desc.bInterfaceProtocol);
  pr_info("Found %d EndPoints\n", iface_desc->desc.bNumEndpoints);
  pr_info("----------------------------------------------------------------\n");

  // endpoint descriptors
  for (i = 0; i < iface_desc->desc.bNumEndpoints; i++)
    {
      int xfertype;
      char *xfertype_str;    

      endpoint = &iface_desc->endpoint[i].desc;
      pr_info("EP[%d]->bLength = %d\n", i, endpoint->bLength);

      pr_info("EP[%d]->bDescriptorType: 0x%02X\n", i, endpoint->bDescriptorType);

      pr_info("EP[%d]->bEndpointAddress: 0x%02X\n", i, endpoint->bEndpointAddress);
      pr_info("---EPNumber=%d, EPDirection=%s\n", 
		      endpoint->bEndpointAddress & USB_ENDPOINT_NUMBER_MASK, 
		      ( (endpoint->bEndpointAddress & USB_ENDPOINT_DIR_MASK) == 0)?"out":"in" );

      pr_info("EP[%d]->bmAttributes: 0x%02X\n", i, endpoint->bmAttributes);
      xfertype = endpoint->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK;
      switch(xfertype)
      {
	      case USB_ENDPOINT_XFER_CONTROL:
		      xfertype_str = "control";
		      break;
	      case USB_ENDPOINT_XFER_ISOC:
		      xfertype_str = "isochronous";
		      break;
	      case USB_ENDPOINT_XFER_BULK:
		      xfertype_str = "bulk";
		      break;
	      case USB_ENDPOINT_XFER_INT:
		      xfertype_str = "interrupt";
		      break;
	      default:
		      xfertype_str = NULL;
		      return -1;
      }
      pr_info("---EPTransferType: %s\n", xfertype_str);

      pr_info("EP[%d]->wMaxPacketSize: 0x%04X (%d)\n", i, endpoint->wMaxPacketSize, endpoint->wMaxPacketSize);
      pr_info("----------------------------------------------------------------\n");
    }

  return 0;
}

static void my_usb_disconnect (struct usb_interface *interface)
{
  pr_info("USB interface %d disconnected\n", interface->cur_altsetting->desc.bInterfaceNumber);
}

static struct usb_device_id my_usb_table[] = {
  {USB_DEVICE (MY_USB_VENDOR, MY_USB_PRODUCT)},
  {}
};
MODULE_DEVICE_TABLE (usb, my_usb_table);

static struct usb_driver my_usb_driver = {
  .name = "my_usb_driver",
  .id_table = my_usb_table,
  .probe = my_usb_probe,
  .disconnect = my_usb_disconnect,
};

static int __init my_init (void)
{
  return usb_register (&my_usb_driver);
}

static void __exit my_exit (void)
{
  usb_deregister (&my_usb_driver);
}

module_init (my_init);
module_exit (my_exit);

MODULE_LICENSE ("GPL");
MODULE_AUTHOR ("CDAC EDD <edd@cadca.gov.in>");
MODULE_DESCRIPTION ("USB stick info driver module");
