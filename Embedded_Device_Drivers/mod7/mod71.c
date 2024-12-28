/* Kernel timer */

#define pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#include <linux/module.h>
#include <linux/init.h>
#include <linux/timer.h>
#include <linux/jiffies.h>
#include <linux/delay.h>

#define TIME_INTVL	(10)	// milliseconds

// define a kernel timer
static struct timer_list my_timer;

static int count = 0;

// callback function for the kernel timer
void my_timer_cb(struct timer_list *tmr)
{
	int ctx = in_interrupt();
	pr_info("In timer, count=[%d], running in %s context\n", count++,
			(ctx==0?"kernel":"interrupt") );

	// reload timer with same data - to ensure regular timer start-expiry
	mod_timer(&my_timer, jiffies + msecs_to_jiffies(TIME_INTVL));
	
	return;
}

static int __init my_mod_init(void)
{
	pr_info("Hello world from %s!\n", KBUILD_MODNAME);
	
	timer_setup(&my_timer, my_timer_cb, 0);
	pr_info("Kernel timer created!\n");

	mod_timer(&my_timer, jiffies + msecs_to_jiffies(TIME_INTVL));

	pr_info("Kernel timer started\n");
	
	return 0;
}

static void __exit my_mod_exit(void)
{
	del_timer(&my_timer);
	pr_info("Deleted kernel timer!\n");
	pr_info("Goodbye world from %s!\n", KBUILD_MODNAME);

	return;
}

module_init(my_mod_init);
module_exit(my_mod_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("EDD <edd@cdac.gov.in>");
MODULE_DESCRIPTION("Module to demo kernel timer!");
