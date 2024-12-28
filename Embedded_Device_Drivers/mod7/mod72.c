/* Kernel high res timer */

#define pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#include <linux/module.h>
#include <linux/init.h>
#include <linux/hrtimer.h>
#include <linux/ktime.h>

#define TIME_INTVL_SECS		(0)		// seconds
#define TIME_INTVL_NSECS	(1000000000UL) 	// nanoseconds

// define a kernel timer
static struct hrtimer my_hrtimer;

static int count = 0;

// callback function for the kernel HR timer
enum hrtimer_restart my_timer_cb(struct hrtimer *hrtmr)
{
	pr_info("Inside HR timer! val=[%d]\n", count++);

	// forward HR timer
	hrtimer_forward_now(hrtmr, ktime_set(TIME_INTVL_SECS, TIME_INTVL_NSECS));
	
	return HRTIMER_RESTART;
}

static int __init my_mod_init(void)
{
	ktime_t ktime;

	pr_info("Hello world from %s!\n", KBUILD_MODNAME);
	
	ktime = ktime_set(TIME_INTVL_SECS, TIME_INTVL_NSECS);
	hrtimer_init(&my_hrtimer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	my_hrtimer.function = my_timer_cb;
	pr_info("Kernel HR timer created!\n");

	hrtimer_start(&my_hrtimer, ktime, HRTIMER_MODE_REL);

	return 0;
}

static void __exit my_mod_exit(void)
{
	hrtimer_cancel(&my_hrtimer);
	pr_info("Deleted kernel HR timer!\n");
	pr_info("Goodbye world from %s!\n", KBUILD_MODNAME);

	return;
}

module_init(my_mod_init);
module_exit(my_mod_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("EDD <edd@cdac.gov.in>");
MODULE_DESCRIPTION("Module to demo kernel's high resolution timer!");
