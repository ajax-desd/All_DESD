/* Symbol export: This module exports symbols */

#define pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/string.h>

#define STR_SZ	(10)

char *mod51_string = NULL;
EXPORT_SYMBOL(mod51_string);

void mod51_func(char *str)
{
	pr_info("Exported function %s called", __func__);
#define MIN(a,b)	((a)<(b)?(a):(b))
	snprintf(mod51_string, MIN(STR_SZ, strlen(str)), str);
	return;
}
EXPORT_SYMBOL(mod51_func);
	
static int __init my_mod_init(void)
{
	pr_info("Hello world from %s!\n", KBUILD_MODNAME);
	mod51_string = (char *)kmalloc(STR_SZ, GFP_KERNEL);
	if (!mod51_string)
	{
		pr_err("Cannot alloc memory in kernel");
		return -1;
	}
	return 0;
}

static void __exit my_mod_exit(void)
{
	pr_info("Goodbye world from %s!\n", KBUILD_MODNAME);
	kfree(mod51_string);
	return;
}

module_init(my_mod_init);
module_exit(my_mod_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("EDD <edd@cdac.gov.in>");
MODULE_DESCRIPTION("Symbol exporting module!");
