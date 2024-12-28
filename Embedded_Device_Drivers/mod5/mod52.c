/* Symbol export: This module uses exported symbols */

#define pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#include <linux/module.h>
#include <linux/init.h>

extern char *mod51_string;
extern void mod51_func(char *str);
	
static int __init my_mod_init(void)
{
	pr_info("Hello world from %s!\n", KBUILD_MODNAME);
	// call exported function from mod51
	mod51_func("String from mod52");
	
	// access exported variable from mod51
	pr_info("String in mod51 is: %s\n", mod51_string);

	return 0;
}

static void __exit my_mod_exit(void)
{
	pr_info("Goodbye world from %s!\n", KBUILD_MODNAME);
	return;
}

module_init(my_mod_init);
module_exit(my_mod_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("EDD <edd@cdac.gov.in>");
MODULE_DESCRIPTION("Module using exported symbols!");
