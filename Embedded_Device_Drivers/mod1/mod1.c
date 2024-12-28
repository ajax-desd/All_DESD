/* Basic kernel module skeleton */

#define pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#include <linux/module.h>
#include <linux/init.h>

static char string[] = "CDAC";
static int num = -100;

static int __init my_mod_init(void)
{
	pr_info("Hello world %s!\n", string);
	return 0;
}

static void __exit my_mod_exit(void)
{
	pr_alert("Goodbye world %d!\n", num);
	return;
}

module_init(my_mod_init);
module_exit(my_mod_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("EDD <edd@cdac.gov.in>");
MODULE_DESCRIPTION("Hello world module!");
