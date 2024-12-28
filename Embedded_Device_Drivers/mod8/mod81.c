/* Illustrate module parameters with callbacks */

#define pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/kthread.h>


#define TIME_INTVL	(1000)	// milliseconds
// instantiation with default, overriden by insmod if any


static int Sleep_time = TIME_INTVL;


static struct task_struct *thread1;
static char thread1_name[] = "Thread-1";
//module_param(Sleep_time,uint,0644);

int thread_func1(void *pv)
{
	int i = 0;
	while(!kthread_should_stop())
	{
		pr_info("In thread %s, i=%d\n", __func__, i++);
		//pr_info("sleep %d\n",Sleep_time);
		msleep(Sleep_time);
	}
	return 0;
}

int notify_on_set(const char *val, const struct kernel_param *kp)
{
	int ans = param_get_uint(val, kp);
	if (ans==0)
	{
		pr_info("Callback function %s called\n", __func__);
		pr_info("New value of Sleep_time = %d\n", Sleep_time);
		return 0;
	}
	return -1;
}

const struct kernel_param_ops myops = 
{
	.set = &notify_on_set,		// my function - overrides default
	.get = &param_get_uint, 	// kernel's function - default
};


// perms: all can read, only USR (root) can write/edit
module_param_cb(Sleep_time, &myops, &Sleep_time, S_IRUGO | S_IWUSR);

// create MODULE DESC strings for modinfo
MODULE_PARM_DESC(Sleep_time, "This is a int Sleep_time with callback");

static int __init my_mod_init(void)
{
	pr_info("Hello world from %s!\n", KBUILD_MODNAME);

	thread1 = kthread_run(thread_func1, NULL, thread1_name);
	if (thread1)
		pr_info("Thread %s created!\n", thread1_name);
	else
	{
		pr_err("Cannot create thread %s\n", thread1_name);
		goto r_thread1;
	}

	
	return 0;

r_thread2:
	kthread_stop(thread1);
r_thread1:
	return -1;
}

static void __exit my_mod_exit(void)
{
	kthread_stop(thread1);
	
	pr_info("Goodbye world from %s!\n", KBUILD_MODNAME);

	return;
}

module_init(my_mod_init);
module_exit(my_mod_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("EDD <edd@cdac.gov.in>");




