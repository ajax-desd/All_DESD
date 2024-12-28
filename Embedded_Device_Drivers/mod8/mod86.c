/* Kernel threads with read-write locks */

#define pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#include <linux/module.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/kthread.h>
#include <linux/string.h>
#include <linux/rwlock.h>
#include <linux/slab.h>

#define WTIME_INTVL	(1000)	// milliseconds
#define RTIME_INTVL	(1000)	// milliseconds
#define BUF_SZ		(1024)	// in bytes
#define  n		10
// define thread structs
static struct task_struct *wthread, **rthread;
static char wthread_name[] = "WThread";
static char rthread_name[] = "RThread-";


// shared data - wthread writes, rthreads only read
static int count = 0;

// rwlock
static DEFINE_RWLOCK(my_rwlock);

int wthread_func(void *pv)
{
	char buffer[20] = {0};

	while(!kthread_should_stop())
	{
		write_lock(&my_rwlock);
		sprintf(buffer, "%s:%d->%d", wthread_name, count++, count);
		pr_info("In thread %s, got wlock, buffer=%s\n", __func__, buffer);
		write_unlock(&my_rwlock);
		msleep(WTIME_INTVL);
	}
	do_exit(0);
	return 0;
}

int rthread_func(void *pv)
{
	char buffer[20] = {0};
	char *thread_name = (char *)pv;

	while(!kthread_should_stop())
	{
		read_lock(&my_rwlock);
		sprintf(buffer, "%s:%d", thread_name, count);
		pr_info("In thread %s, got rlock, buffer=%s\n", __func__, buffer);
		read_unlock(&my_rwlock);
		msleep(RTIME_INTVL);
	}
	do_exit(0);
	return 0;
}

static int __init my_mod_init(void)
{
	int i,j;
	char **buf ;
	pr_info("Hello world from %s!\n", KBUILD_MODNAME);
	buf = kmalloc(sizeof(char*) * n, GFP_KERNEL);

	
	wthread = kthread_run(wthread_func, NULL, wthread_name);
	if (wthread)
		pr_info("Thread %s created!\n", wthread_name);
	else
	{
		pr_err("Cannot create thread %s\n", wthread_name);
		goto r_thread1;
	}

	

	for(i =0;i<n;i++)
	{	
		buf[i]=kmalloc(sizeof(char) * n, GFP_KERNEL);
		sprintf(buf[i], "%s:%d", rthread_name, i);
		rthread[i] = kthread_run(rthread_func, &buf[i], buf[i]);
		if (rthread[i])
			pr_info("Thread %s created!\n", buf);
		else
		{
			pr_err("Cannot create thread %s\n", buf);
			goto r_thread;
		}
	}
	return 0;

r_thread:
	for(j=0;j<i;j++){
		kthread_stop(rthread[i]);
	}
	kthread_stop(wthread);
r_thread1:
	return -1;
}

static void __exit my_mod_exit(void)
{	
	int i;
	kthread_stop(wthread);
	for(i=0;i<n;i++){
		kthread_stop(rthread[i]);
	}
	
	
	pr_info("Goodbye world from %s!\n", KBUILD_MODNAME);

	return;
}

module_init(my_mod_init);
module_exit(my_mod_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("EDD <edd@cdac.gov.in>");
MODULE_DESCRIPTION("Module to demo rwlock!");
