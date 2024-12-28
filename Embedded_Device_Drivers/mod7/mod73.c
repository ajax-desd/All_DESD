/* Getting time diffs */

#define pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#include <linux/module.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/ktime.h>

static int __init my_mod_init(void)
{
	ktime_t start, end, elapsed;
	unsigned int msecs = 1500;
	long long sleeps = msecs*1E6;

	pr_info("Hello world from %s!\n", KBUILD_MODNAME);

	pr_info("Sleeping for %lld nsecs...\n", sleeps);
	start = ktime_get();
	msleep(msecs);
	end = ktime_get();
	elapsed = end - start;
	pr_info("Elapsed time %lld nsecs\n", ktime_to_ns(elapsed));

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
MODULE_DESCRIPTION("Module to demo time differencing!");
