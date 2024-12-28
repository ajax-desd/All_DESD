/* Illustrate module parameters with callbacks */

#define pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>

// instantiation with default, overriden by insmod if any
static short myshort = 100;

int notify_on_set(const char *val, const struct kernel_param *kp)
{
	int ans = param_set_short(val, kp);
	if (ans==0)
	{
		pr_info("Callback function %s called\n", __func__);
		pr_info("New value of myshort = %d\n", myshort);
		return 0;
	}
	return -1;
}

const struct kernel_param_ops myops = 
{
	.set = &notify_on_set,		// my function - overrides default
	.get = &param_get_short, 	// kernel's function - default
};

// perms: all can read, only USR (root) can write/edit
module_param_cb(myshort, &myops, &myshort, S_IRUGO | S_IWUSR);

// create MODULE DESC strings for modinfo
MODULE_PARM_DESC(myshort, "This is a short-int variable with callback");

static int __init my_mod_init(void)
{
	pr_info("Hello from mod22!\n");
	pr_info("myshort = %d\n", myshort);
	return 0;
}

static void __exit my_mod_exit(void)
{
	pr_info("Goodbye from mod22!\n");

	return;
}

module_init(my_mod_init);
module_exit(my_mod_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("EDD <edd@cdac.gov.in>");
MODULE_DESCRIPTION("Module with param callback support!");
