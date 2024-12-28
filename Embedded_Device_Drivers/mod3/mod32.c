/* Major:Minor dynamic allottment */

#define pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>

#define MY_DEV_NAME	"cdac_edd"
dev_t dev = 0;

static int __init my_mod_init(void)
{
	int ans;

	pr_info("Hello world from mod32!\n");
	ans = alloc_chrdev_region(&dev, 0, 1, MY_DEV_NAME);
	if (ans<0)
	{
		pr_info("Error in major:minor allotment!\n");
		return -1;
	}
	pr_info("major:minor %d:%d allotted!\n", MAJOR(dev),MINOR(dev));
	return 0;
}

static void __exit my_mod_exit(void)
{
	pr_info("Goodbye world from mod32!\n");
	unregister_chrdev_region(dev, 1);
	pr_info("major:minor numbers freed up...\n");
	return;
}

module_init(my_mod_init);
module_exit(my_mod_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("EDD <edd@cdac.gov.in>");
MODULE_DESCRIPTION("major:minor dynamic allotment module!");
