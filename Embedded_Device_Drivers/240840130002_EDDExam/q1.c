/* Kernel timer */

#define pr_fmt(fmt)	KBUILD_MODNAME ": " fmt


//header files
#include <linux/module.h>
#include <linux/init.h>
#include <linux/timer.h>
#include <linux/jiffies.h>
#include <linux/delay.h>

#define TIME_INTVL	(5000)	// milliseconds

// define a kernel timer
static struct timer_list my_timer;

//gloabal countmainter for callbacks
static int count = 0;

// callback function for the kernel timer
void my_timer_cb(struct timer_list *tmr)
{
	int ctx = in_interrupt();
	//cx is use it is in interrupt mode or kernel context
	//count is for incrementing every 5 sec
	pr_info("In timer, count=[%d], running in %s context\n", count++,
			(ctx==0?"kernel":"interrupt") );

	// reload timer with same data - to ensure regular timer start-expiry
	mod_timer(&my_timer, jiffies + msecs_to_jiffies(TIME_INTVL));
	
	return;
}

//staring of module
static int __init my_mod_init(void)
{
	pr_info("Hello world from %s!\n", KBUILD_MODNAME);
	
	//setting up the timer
	timer_setup(&my_timer, my_timer_cb, 0);
	pr_info("Kernel timer created!\n");
	
	//start the timer
	mod_timer(&my_timer, jiffies + msecs_to_jiffies(TIME_INTVL));
	//when timer expires it cal its callback function
	pr_info("Kernel timer started\n");
	
	return 0;
}

//exiting of module

static void __exit my_mod_exit(void)
{	
	//delete the timer
	del_timer(&my_timer);
	pr_info("Deleted kernel timer!\n");
	pr_info("Goodbye world from %s!\n", KBUILD_MODNAME);

	return;
}


//module int and exit classify
module_init(my_mod_init);
module_exit(my_mod_exit);

MODULE_LICENSE("GPL");//GPL is licence we nee to give it 
MODULE_AUTHOR("Ajay Singh-240840130002");
MODULE_DESCRIPTION("Q1  kernel timer");
