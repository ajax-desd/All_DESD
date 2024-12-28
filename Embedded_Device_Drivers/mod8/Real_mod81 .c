/* Kernel thread basics */

#define pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#include <linux/module.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/kthread.h>

#define TIME_INTVL	(1000)	// milliseconds
#define n 4
// define thread structs
//static struct task_struct *thread1, *thread2;
static struct task_struct thread[n];
static char thread1_name[] = "Thread-1";
static char thread2_name[] = "Thread-2";

int thread_func1(void *pv)
{
	int i = 0;
	while(!kthread_should_stop())
	{
		pr_info("In thread %s, i=%d\n", __func__, i++);
		msleep(TIME_INTVL);
	}
	return 0;
}



int thread_func2(void *pv)
{
	int i = 0;
	while(!kthread_should_stop())
	{
		pr_info("In thread %s, i=%d\n", __func__, i++);
		msleep(TIME_INTVL*2);
	}
	return 0;
}

static int __init my_mod_init(void)
{
	int i,j;
	pr_info("Hello world from %s!\n", KBUILD_MODNAME);

	
	char buffer[15]={0};
	
	
	
	
	for(i=1;i<n+1;i++){
	       //snprintf(buffer, sizeof(buffer), "%s%s", thread_func1, i);
		thread[i] = kthread_run(&buffer, NULL, thread1_name);
		if (thread[i]){
		pr_info("Thread %s created!\n", thread2_name);
		memset(buffer,0,sizeof(buffer));
		}
		else
		{
			pr_err("Cannot create thread %s\n", thread2_name);
			goto r_thread;
		}
		
	}
	return 0;

r_thread:
	for(j=1;j<i;j++){
		kthread_stop(thread[j]);
	}
	return -1;
}

static void __exit my_mod_exit(void)
{	
	int i;
	for(i=1;i<n+1;i++){
		kthread_stop(thread[i]);
	}	
	pr_info("Goodbye world from %s!\n", KBUILD_MODNAME);

	return;
}

module_init(my_mod_init);
module_exit(my_mod_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("EDD <edd@cdac.gov.in>");
MODULE_DESCRIPTION("Module to demo kernel threads!");
