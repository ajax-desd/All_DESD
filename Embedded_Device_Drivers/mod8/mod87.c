/* Kernel threads with seq locks */

#define pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#include <linux/module.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/kthread.h>
#include <linux/string.h>
#include <linux/seqlock.h>

#define WTIME_INTVL	(250)	// milliseconds
#define RTIME_INTVL	(1000)	// milliseconds
#define BUF_SZ		(1024)	// in bytes

// define thread structs
static struct task_struct *wthread, *rthread;
static char wthread_name[] = "WThread";
static char rthread_name[] = "RThread";

// shared data - wthread writes, rthread reads
static int count = 0;

// rwlock
static seqlock_t my_seqlock;

int wthread_func(void *pv)
{
	char buffer[20] = {0};

	while(!kthread_should_stop())
	{
		write_seqlock(&my_seqlock);
		sprintf(buffer, "%s:%d->%d", wthread_name, count++, count);
		pr_info("In thread %s, got seqlock, buffer=%s\n", __func__, buffer);
		write_sequnlock(&my_seqlock);
		msleep(WTIME_INTVL);
	}
	return 0;
}

int rthread_func(void *pv)
{
	char buffer[20] = {0};
	char *thread_name = (char *)pv;

	unsigned int seq_no;
	unsigned int read_value;

	while(!kthread_should_stop())
	{
		do
		{
			seq_no = read_seqbegin(&my_seqlock);
			pr_info("Read try - seq_no=%d", seq_no);
			read_value = count;
		} 
		while (read_seqretry(&my_seqlock, seq_no));
		pr_info("Read done - seq_no=%d", seq_no);

		sprintf(buffer, "%s:%d", thread_name, count);
		pr_info("In thread %s, buffer=%s\n", __func__, buffer);
		msleep(RTIME_INTVL);
	}
	return 0;
}

static int __init my_mod_init(void)
{
	pr_info("Hello world from %s!\n", KBUILD_MODNAME);

	seqlock_init(&my_seqlock);

	wthread = kthread_run(wthread_func, NULL, wthread_name);
	if (wthread)
		pr_info("Thread %s created!\n", wthread_name);
	else
	{
		pr_err("Cannot create thread %s\n", wthread_name);
		goto r_thread1;
	}

	rthread = kthread_run(rthread_func, rthread_name, rthread_name);
	if (rthread)
		pr_info("Thread %s created!\n", rthread_name);
	else
	{
		pr_err("Cannot create thread %s\n", rthread_name);
		goto r_thread2;
	}

	return 0;

r_thread2:
	kthread_stop(wthread);
r_thread1:
	return -1;
}

static void __exit my_mod_exit(void)
{
	kthread_stop(wthread);
	kthread_stop(rthread);
	pr_info("Goodbye world from %s!\n", KBUILD_MODNAME);

	return;
}

module_init(my_mod_init);
module_exit(my_mod_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("EDD <edd@cdac.gov.in>");
MODULE_DESCRIPTION("Module to demo seqlock!");
