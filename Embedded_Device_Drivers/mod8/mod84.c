/* Kernel threads with mutex-protected shared variables */

#define pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#include <linux/module.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/kthread.h>
#include <linux/string.h>
#include <linux/mutex.h>
#include <linux/slab.h>

#define TIME_INTVL	(1000)	// milliseconds
#define BUF_SZ		(1024)	// in bytes
#define n		10
// define thread structs
static struct task_struct **thread;
static char thread_name[] = "Thread-";

// shared data
static int count = 100;
static char buffer[BUF_SZ] = {0};

// mutex protector
struct mutex my_mutex;

int thread_func1(void *pv)
{	
	int num = *(int *)pv;
	msleep((num*TIME_INTVL)%num);
	while(!kthread_should_stop())
	{
		mutex_lock(&my_mutex);
		pr_info("%s%d got mutex!\n", thread_name, num);
		//memset(buffer, 0, BUF_SZ);
		msleep(TIME_INTVL);
		//sprintf(buffer, "%s:%d", thread1_name, count++);
		if(num % 2 == 0)
			count++;
		else
			count--;
		msleep(TIME_INTVL);
		pr_info("In thread %d, count=%d\n", num, count);
		mutex_unlock(&my_mutex);
		msleep(TIME_INTVL);
	}
	return 0;
}



static int __init my_mod_init(void)
{	
	int i; 
	char buff[10] = {0};
	pr_info("Hello world from %s!\n", KBUILD_MODNAME);
	mutex_init(&my_mutex);
	//int * k=kmalloc(sizeof(int)*n,GFP_KERNEL);
	thread=kmalloc(sizeof(struct task_struct *)*n,GFP_KERNEL);
	
	for(i=0;i<n;i++){
		//k[i]=i;
		sprintf(buff,"%s%d",thread_name,i);
		thread[i] = kthread_run(thread_func1, (void *)&i, buff);
		if (thread[i])
			pr_info("Thread %s created!\n", buff);
		else
		{
			pr_err("Cannot create thread %s\n", buff);
			goto r_thread;
		}
	}

	
	return 0;

r_thread:
	kthread_stop(thread[i]);

	return -1;
}

static void __exit my_mod_exit(void)
{
	int i;
	for(i = 0; i < n; i++)
	{
		kthread_stop(thread[i]);
	}
	kfree(thread);
	pr_info("Goodbye world from %s!\n", KBUILD_MODNAME);

	return;
}

module_init(my_mod_init);
module_exit(my_mod_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("EDD <edd@cdac.gov.in>");
MODULE_DESCRIPTION("Module to demo mutex-protected shared variables!");
