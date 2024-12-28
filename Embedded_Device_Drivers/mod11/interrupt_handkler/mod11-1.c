/* LED control and blinking via GPIO */

#define pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#include <linux/init.h>
#include <linux/module.h>
#include <linux/gpio.h>       
#include <linux/kobject.h>    
#include <linux/kthread.h>    
#include <linux/delay.h>      

static struct kobject *kobj_ref;            
static struct task_struct *task;            
					    
static unsigned int gpioLED = 60;          

static unsigned int blinkPeriod = 1000;     // in msecs
module_param(blinkPeriod, uint, S_IRUGO | S_IWUSR);   
MODULE_PARM_DESC(blinkPeriod, "LED blink period in ms (min=1, default=1000, max=10000)");

static char ledName[10] = {0};
static bool ledOn = 0;                      
enum modes { OFF, ON, FLASH };          // LED modes    
static enum modes mode = FLASH;		// default LED mode

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
   return sprintf(buf, "%d\n", blinkPeriod);
}

static ssize_t period_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
   unsigned int period;                    

   sscanf(buf, "%du", &period);             
   if ((period>1)&&(period<=10000)){        
      blinkPeriod = period;                 
   }
   pr_info("Period set to %d\n", blinkPeriod);

   return sizeof(period);
}

static struct kobj_attribute period_attr = __ATTR(blinkPeriod, 0664, period_show, period_store);
static struct kobj_attribute mode_attr = __ATTR(mode, 0664, mode_show, mode_store);

static struct attribute *led_attrs[] = {
   &period_attr.attr,                       
   &mode_attr.attr,                         
   NULL,//sentinant value
};

static struct attribute_group attr_group = {
   .name  = ledName,                        
   .attrs = led_attrs,                      
};

static int flash_led(void *arg)
{
   pr_info("LED flashing thread started with period=%d\n", blinkPeriod);

   while(!kthread_should_stop()){          
      if (mode==FLASH) ledOn = !ledOn;  
      else if (mode==ON) ledOn = true;
      else ledOn = false;

      gpio_set_value(gpioLED, ledOn);      
					   
      msleep(blinkPeriod/2);   //50 percent duty cycle             
   }

   pr_info("LED Flashing thread exiting\n");
   return 0;
}

static int __init my_init(void){
   int result = 0;

   sprintf(ledName, "led%d", gpioLED);  
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

   result = gpio_request(gpioLED, "sysfs");          
   if (result<0)
   {
      pr_err("Error in gpio request!\n");
      goto r_gpio_req;
   } 

   ledOn = true;
   gpio_direction_output(gpioLED, ledOn);   
   gpio_export(gpioLED, false);  		// export in /sys/class/gpio/...

   task = kthread_run(flash_led, NULL, "LED blink thread"); 
   if(IS_ERR(task))
   {                                     
      pr_err("Failed to create LED flashing task\n");
      goto r_task;
   }

   return 0;

r_task:
   gpio_set_value(gpioLED, 0);
   gpio_unexport(gpioLED);
   gpio_free(gpioLED);
r_gpio_req:
   sysfs_remove_group(kobj_ref, &attr_group);
r_sys_grp:
   kobject_put(kobj_ref);
   return -1;

}

static void __exit my_exit(void)
{
   kthread_stop(task);

   gpio_set_value(gpioLED, 0);              
   gpio_unexport(gpioLED);                  
   gpio_free(gpioLED);                      
   pr_info("GPIO %d freed up\n", gpioLED);

   sysfs_remove_group(kobj_ref, &attr_group);   
   kobject_put(kobj_ref);                  

   printk(KERN_INFO "Good bye from %s!\n", KBUILD_MODNAME);
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("CDAC EDD <edd@cdac.gov.in>");
MODULE_DESCRIPTION("A simple LED driver using GPIOs");
