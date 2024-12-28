/* Basic kernel module skeleton - file2 */

#define pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#include <linux/module.h>
#include <linux/init.h>

void __exit my_mod_exit(void)
{
	pr_info("Goodbye world from %s!\n", KBUILD_MODNAME);
	return;
}

module_exit(my_mod_exit);
