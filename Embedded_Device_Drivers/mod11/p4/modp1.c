/* LED control and blinking via GPIO */

#define pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#include <linux/init.h>
#include <linux/module.h>
#include <linux/gpio.h>       
#include <linux/kobject.h>    
#include <linux/kthread.h>    
#include <linux/delay.h>      
#include <linux/fs.h>
#include <linux/err.h>
#include <linux/device.h>
#include <linux/kdev_t.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/timer.h>
#include <linux/jiffies.h>
#include <linux/delay.h>
#include "my_ioctls.h"
#define TIME_INTVL	(1000)	// milliseconds



//static int count = 0;+
#define MY_CLASS_NAME	"cdac_cls"
#define MY_DEV_NAME	"cdac_dev"
#define MY_KBUF_SZ	(1024)

dev_t dev = 0;
static struct class *dev_class;
static struct device *cdevice;
static struct cdev my_cdev;
char *kbuf;
static struct kobject *kobj_ref;            
static struct task_struct *task;            
// define a kernel timer
static struct timer_list my_timer;				    
static unsigned int gpioLED1 =60,gpioLED2=48,gpioLED3=49,gpioLED4=47;          
static unsigned int type =10;
static int my_open(struct inode *inode, struct file *file);
static ssize_t my_read(struct file *file, char __user *buf, size_t len, loff_t *off);
static ssize_t my_write(struct file *file, const char __user *buf, size_t len, loff_t *off);
static int my_release(struct inode *inode, struct file *file);
static unsigned int num = 0; 
    // in msecs
   // static unsigned int num = 1000;
module_param(num, uint, S_IRUGO | S_IWUSR);   
MODULE_PARM_DESC(num, "LED blink period in ms (min=1, default=0, max=15)");

static char ledName[10] = {0};
static bool ledOn = 0;                      
enum modes { OFF, ON, FLASH };          // LED modes    
static enum modes mode = ON;		// default LED mode

static ssize_t mode_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf){
   switch(mode){
      case OFF:   return sprintf(buf, "off\n");       
      case ON:    return sprintf(buf, "on\n");
      case FLASH: return sprintf(buf, "flash\n");
      default:    return sprintf(buf, "error\n"); 
   }
}

static ssize_t mode_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count){
   if (strncmp(buf,"on",count-1)==0) { mode = ON; }   
   else if (strncmp(buf,"off",count-1)==0) { mode = OFF; }
   else if (strncmp(buf,"flash",count-1)==0) { mode = FLASH; }

   return count;
}

static ssize_t period_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
   return sprintf(buf, "%d\n", num);
}

static ssize_t period_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
   unsigned int period;                    

   sscanf(buf, "%du", &period);             
   if ((period>=0)&&(period<=15)){        
      num = period;                 
   }
   pr_info("Period set to %d\n", num);

   return sizeof(period);
}


static int my_open(struct inode *inode, struct file *file)
{
	pr_info("My open function %s called\n", __func__);
	return 0;
}

static ssize_t my_read(struct file *file, char __user *buf, size_t len, loff_t *off)
{
	pr_info("My read function %s called\n", __func__);
	if ( copy_to_user(buf, kbuf + *off, len) )
	{
		pr_err("Error in data write to userspace!\n");
	}
	pr_info("Data written to userspace\n");
	*off += len;
	return len;
}

static long my_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{	
	
	switch(cmd)
	{
		case COUNT_UP:
			if(type==1){
			   break;
			}
			type=1;
			num=0;
			break;
		case COUNT_DOWN:
			if(type==0){
			   break;
			}
			type=0;
			num=15;
			break;
		default:
			pr_err("Undefined command!\n");
			break;
	}
	mod_timer(&my_timer, jiffies + msecs_to_jiffies(TIME_INTVL));
	return 0;
}

static ssize_t my_write(struct file *file, const char __user *buf, size_t len, loff_t *off)
{
int num1;
	pr_info("My write function %s called\n", __func__);
	if ( copy_from_user(&num1, buf, sizeof(int)) )
	{
		pr_err("Error in data read from userspace!\n");
	}
	pr_info("Data read from userspace!\n");
	num=num1;
	pr_info("value on the LEDs are %d\n",num1);
	return sizeof(int);
}

static int my_release(struct inode *inode, struct file *file)
{
	pr_info("My release function %s called\n", __func__);
	return 0;
}

// create a fops struct
static struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = my_open,
	.read = my_read,
	.write = my_write,
	.release = my_release,
	.unlocked_ioctl =my_ioctl,
};




static struct kobj_attribute period_attr = __ATTR(num, 0664, period_show, period_store);
static struct kobj_attribute mode_attr = __ATTR(mode, 0664, mode_show, mode_store);

static struct attribute *led_attrs[] = {
   &period_attr.attr,                       
   &mode_attr.attr,                         
   NULL,//sentinant value
};

static struct attribute_group attr_group = {
   .name = ledName,               
   .attrs = led_attrs,                      
};

static int flash_led(void *arg)
{
   pr_info("LED flashing thread started with period=%d\n", num);

   while(!kthread_should_stop()){          
     if (mode==ON){
    
      ledOn = true;
      
        gpio_set_value(gpioLED1, (num & 0x01));   
        gpio_set_value(gpioLED2, (num & 0x02));  
        gpio_set_value(gpioLED3, (num & 0x04));   
        gpio_set_value(gpioLED4, (num & 0x08));
        } 
      else{ 
      ledOn = false;
     gpio_set_value(gpioLED1, ledOn);   
        gpio_set_value(gpioLED3, ledOn);  
        gpio_set_value(gpioLED4, ledOn);   
        gpio_set_value(gpioLED2, ledOn);
      
      }
					   
      //msleep(500);   //50 percent duty cycle             
   }

   pr_info("LED Flashing thread exiting\n");
   return 0;
}

void my_timer_cb(struct timer_list *tmr)
{
	int ctx = in_interrupt();
	pr_info("In timer, count=[%d], running in %s context\n", num,
			(ctx==0?"kernel":"interrupt") );
	if(type==1)
	{
		if(num==15)
		{num=0;}
		else{ num++;}
	}
	if(type==0){
		if(num==0)
		{num=15;}
		else{ num--;}
	}
	// reload timer with same data - to ensure regular timer start-expiry
	mod_timerm(&y_timer, jiffies + msecs_to_jiffies(TIME_INTVL));
	
	return;
}


static int __init my_init(void){
   int result = 0,ans;
   kbuf = (char *)kmalloc(MY_KBUF_SZ, GFP_KERNEL);
	if (!kbuf)
	{
		pr_err("Cannot allocate kernel memory!\n");
		return -1;
	}

	pr_info("Hello world from mod35!\n");
	ans = alloc_chrdev_region(&dev, 0, 1, MY_DEV_NAME);
	if (ans<0)
	{
		pr_err("Error in major:minor allotment!\n");
		goto r_kbuf;
	}
	pr_info("major:minor %d:%d allotted!\n", MAJOR(dev),MINOR(dev));

	// initialize a cdev
	cdev_init(&my_cdev, &fops);

	ans = cdev_add(&my_cdev, dev, 1);
	if (ans<0)
	{
		pr_err("Could not add cdev to the kernel!\n");
		goto r_cdev;
	}

	dev_class = class_create(THIS_MODULE, MY_CLASS_NAME);
	if (IS_ERR(dev_class))
	{
		pr_err("Could not create device class %s\n", MY_CLASS_NAME);
		goto r_class;
	}

	cdevice = device_create(dev_class, NULL, dev, NULL, MY_DEV_NAME);
	if (IS_ERR(cdevice))
	{
		pr_err("Could not create device %s\n", MY_DEV_NAME);
		goto r_device;
	}
	pr_info("Device %s under class %s created with success\n", 
			MY_DEV_NAME, MY_CLASS_NAME);
	
	
   sprintf(ledName, "led%d", gpioLED1);  //
   pr_info("Init'ing GPIO LED %s...\n", ledName);



   kobj_ref = kobject_create_and_add("cdac_led", NULL); // kernel_kobj points to /sys/cdac_edd
   if(!kobj_ref){
      pr_err("Failed to create kobject\n");
      return -ENOMEM;
   }

   // create an attr group
   result = sysfs_create_group(kobj_ref, &attr_group);
   if(result) {
      pr_err("Failed to create sysfs group\n");
      goto r_sys_grp;
   }

   result = gpio_request(gpioLED1, "sysfs");  // 
          
   if (result<0)
   {
      pr_err("Error in gpio request!\n");
      goto r_gpio_req;
   } 
   // create an attr group
   
   result = gpio_request(gpioLED2, "sysfs"); 
   if (result<0)
   {
      pr_err("Error in gpio request!\n");
      goto r_gpio_req;
   } 
   

   // create an attr group
   result = gpio_request(gpioLED3, "sysfs");  // 
          
   if (result<0)
   {
      pr_err("Error in gpio request!\n");
      goto r_gpio_req;
   } 
   
   result = gpio_request(gpioLED4, "sysfs");  // 
          
   if (result<0)
   {
      pr_err("Error in gpio request!\n");
      goto r_gpio_req;
   } 
   ledOn = true;
   gpio_direction_output(gpioLED1, ledOn);// 
   gpio_export(gpioLED1, false);  	//
   gpio_direction_output(gpioLED2, ledOn);  // 
   gpio_export(gpioLED2, false); 
   gpio_direction_output(gpioLED3, ledOn); // 
   gpio_export(gpioLED3, false);
   gpio_direction_output(gpioLED4, ledOn);  // 
   gpio_export(gpioLED4, false);
   
   task = kthread_run(flash_led, NULL, "LED blink thread"); 
   if(IS_ERR(task))
   {                                     
      pr_err("Failed to create LED flashing task\n");
      goto r_task;
   }
   
   timer_setup(&my_timer, my_timer_cb, 0);
	pr_info("Kernel timer created!\n");

   
   return 0;

r_task:
   gpio_set_value(gpioLED1, 0);//
   gpio_unexport(gpioLED1);
   gpio_free(gpioLED1);
   gpio_set_value(gpioLED2, 0);//
   gpio_unexport(gpioLED2);
   gpio_free(gpioLED2);
   gpio_set_value(gpioLED3, 0);//
   gpio_unexport(gpioLED3);
   gpio_free(gpioLED3);
   gpio_set_value(gpioLED4, 0);//
   gpio_unexport(gpioLED4);
   gpio_free(gpioLED4);
r_gpio_req:
   sysfs_remove_group(kobj_ref, &attr_group);
   //if(ledName)
r_sys_grp:
   kobject_put(kobj_ref);
   return -1;
r_device:
	class_destroy(dev_class);
r_class:
	cdev_del(&my_cdev);
r_cdev:
	unregister_chrdev_region(dev, 1);
r_kbuf:
	kfree(kbuf);

	return -1;

}

static void __exit my_exit(void)
{
   kthread_stop(task);

   gpio_set_value(gpioLED1, 0);//
   gpio_unexport(gpioLED1);
   gpio_free(gpioLED1);
   gpio_set_value(gpioLED2, 0);//
   gpio_unexport(gpioLED2);
   gpio_free(gpioLED2);
   gpio_set_value(gpioLED3, 0);//
   gpio_unexport(gpioLED3);
   gpio_free(gpioLED3);
   gpio_set_value(gpioLED4, 0);//
   gpio_unexport(gpioLED4);
   gpio_free(gpioLED4);                   
  // pr_info("GPIO %d freed up\n", gpioLED);
	
   sysfs_remove_group(kobj_ref, &attr_group); 
   kobject_put(kobj_ref);                  
        pr_info("Goodbye world from mod35!\n");
	device_destroy(dev_class, dev);
	class_destroy(dev_class);
	cdev_del(&my_cdev);
	unregister_chrdev_region(dev, 1);
	kfree(kbuf);
	pr_info("major:minor numbers freed up...\n");
   del_timer(&my_timer);
   printk(KERN_INFO "Good bye from %s!\n", KBUILD_MODNAME);
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("CDAC EDD <edd@cdac.gov.in>");
MODULE_DESCRIPTION("A simple LED driver using GPIOs");
