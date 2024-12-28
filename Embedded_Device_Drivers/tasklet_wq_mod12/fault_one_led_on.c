/* Kernel global delayed workqueue - dynamic example */

#define pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#include <linux/init.h>
#include <linux/module.h>
#include <linux/gpio.h>       
#include <linux/kobject.h>   
#include <linux/interrupt.h>
#include <linux/workqueue.h>
#include <linux/delay.h>

static struct kobject *kobj_ref;            

	
// button related
static unsigned int gpioButton = 46; // P8_16
static unsigned int irqNumber;	   
static unsigned int n1 = 5,n2 = 5,n3 = 5,n4 = 5;  // mapped to gpioButton
static unsigned int numPresses = 0;
module_param(n1,uint,0644);
MODULE_DESCRIPTION("n1 for led1");
module_param(n2,uint,0644);
MODULE_DESCRIPTION("n2 for led2");
module_param(n3,uint,0644);
MODULE_DESCRIPTION("n3 for led3");
module_param(n4,uint,0644);
MODULE_DESCRIPTION("n4 for led4");

static bool ledOn = 0;
static unsigned int gpioLED1 = 60, gpioLED2 = 48,gpioLED3 = 49, gpioLED4 = 47;
static char ledName[10] = {0};

// workqueue related
#define MSECS_DELAY	(5000)	     // 5 secs
static struct delayed_work my_dwork;



static ssize_t mode_show1(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
   return sprintf(buf, "%d\n", n1);
}

static ssize_t mode_store1(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
   unsigned int period;                    

   sscanf(buf, "%du", &period);             
   if ((period>=0)&&(period<=15)){        
      n1 = period;                 
   }
   pr_info("Period set to %d\n", n1);

   return sizeof(period);
}
static ssize_t mode_show2(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
   return sprintf(buf, "%d\n", n2);
}

static ssize_t mode_store2(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
   unsigned int period;                    

   sscanf(buf, "%du", &period);             
   if ((period>=0)&&(period<=15)){        
      n2 = period;                 
   }
   pr_info("Period set to %d\n", n2);

   return sizeof(period);
}
static ssize_t mode_show3(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
   return sprintf(buf, "%d\n", n3);
}

static ssize_t mode_store3(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
   unsigned int period;                    

   sscanf(buf, "%du", &period);             
   if ((period>=0)&&(period<=15)){        
      n3 = period;                 
   }
   pr_info("Period set to %d\n", n3);

   return sizeof(period);
}
static ssize_t mode_show4(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
   return sprintf(buf, "%d\n", n4);
}

static ssize_t mode_store4(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
   unsigned int period;                    

   sscanf(buf, "%du", &period);             
   if ((period>=0)&&(period<=15)){        
      n4 = period;                 
   }
   pr_info("Period set to %d\n", n4);

   return sizeof(period);
}

static struct kobj_attribute mode_attr1 = __ATTR(n1, 0664, mode_show1, mode_store1);
static struct kobj_attribute mode_attr2 = __ATTR(n2, 0664, mode_show2, mode_store2);
static struct kobj_attribute mode_attr3 = __ATTR(n3, 0664, mode_show3, mode_store3);
static struct kobj_attribute mode_attr4 = __ATTR(n4, 0664, mode_show4, mode_store4);

static struct attribute *led_attrs1[] = {                  
   &mode_attr1.attr,                         
   NULL,//sentinant value
};
static struct attribute_group attr_group1 = {
   .name = ledName,               
   .attrs = led_attrs1,                      
};
static struct attribute *led_attrs2[] = {                  
   &mode_attr2.attr,                         
   NULL,//sentinant value
};
static struct attribute_group attr_group2 = {
   .name = ledName,               
   .attrs = led_attrs2,                      
};
static struct attribute *led_attrs3[] = {                  
   &mode_attr3.attr,                         
   NULL,//sentinant value
};
static struct attribute_group attr_group3 = {
   .name = ledName,               
   .attrs = led_attrs3,                      
};
static struct attribute *led_attrs4[]= {                  
   &mode_attr4.attr,                         
   NULL,//sentinant value
};
static struct attribute_group attr_group4 = {
   .name = ledName,               
   .attrs = led_attrs4,                      
};

static void my_dwork_func(struct work_struct *dwork)
{
   numPresses++;
   pr_info("Button press interrupt!\n");
        gpio_set_value(gpioLED1, (numPresses & 0x01));   
        gpio_set_value(gpioLED2, (numPresses & 0x02));  
        gpio_set_value(gpioLED3, (numPresses & 0x04));   
        gpio_set_value(gpioLED4, (numPresses & 0x08)); 
   pr_info("In %s: numPressed = %d\n", __func__, numPresses);
}

static irq_handler_t button_handler(unsigned int irq, void *dev_id, struct pt_regs *regs)
{
   pr_info("In button press interrupt!\n");

   pr_info("Scheduling delayed work...\n");
   schedule_delayed_work(&my_dwork, msecs_to_jiffies(10));

   pr_info("Exiting interrupt handler\n");
   
   return (irq_handler_t) IRQ_HANDLED;
}

static int __init my_init(void){
   int result = 0;
   
   kobj_ref = kobject_create_and_add("cdac_led", NULL); // Create the kobject
   if (!kobj_ref) {
      pr_err("Failed to create kobject\n");
      return -ENOMEM;
   }

   pr_info("Setting up IRQ for GPIO %d for button\n", gpioButton);

   // Request the GPIO for the button
   if (!gpio_is_valid(gpioButton)) {
      pr_err("Invalid GPIO for button!\n");
      result = -ENODEV;
      goto r_kobject;  // Jump to clean up the kobject
   }

   result = gpio_request(gpioButton, "sysfs");
   if (result < 0) {
      pr_err("Failed to request GPIO for button\n");
      goto r_kobject;  // Jump to clean up the kobject
   }

   // Request and set up the LEDs and sysfs groups
   result = gpio_request(gpioLED1, "sysfs");
   if (result < 0) {
      pr_err("Failed to request GPIO for LED1\n");
      goto r_gpio_button;  // Jump to clean up button GPIO
   }

   result = sysfs_create_group(kobj_ref, &attr_group1);
   if (result) {
      pr_err("Failed to create sysfs group for LED1\n");
      goto r_gpio_led1;  // Jump to clean up LED1 GPIO
   }

   result = gpio_request(gpioLED2, "sysfs");
   if (result < 0) {
      pr_err("Failed to request GPIO for LED2\n");
      goto r_sysfs_group1;  // Jump to clean up sysfs group for LED1
   }

   result = sysfs_create_group(kobj_ref, &attr_group2);
   if (result) {
      pr_err("Failed to create sysfs group for LED2\n");
      goto r_gpio_led2;  // Jump to clean up LED2 GPIO
   }

   result = gpio_request(gpioLED3, "sysfs");
   if (result < 0) {
      pr_err("Failed to request GPIO for LED3\n");
      goto r_sysfs_group2;  // Jump to clean up sysfs group for LED2
   }

   result = sysfs_create_group(kobj_ref, &attr_group3);
   if (result) {
      pr_err("Failed to create sysfs group for LED3\n");
      goto r_gpio_led3;  // Jump to clean up LED3 GPIO
   }

   result = gpio_request(gpioLED4, "sysfs");
   if (result < 0) {
      pr_err("Failed to request GPIO for LED4\n");
      goto r_sysfs_group3;  // Jump to clean up sysfs group for LED3
   }

   result = sysfs_create_group(kobj_ref, &attr_group4);
   if (result) {
      pr_err("Failed to create sysfs group for LED4\n");
      goto r_gpio_led4;  // Jump to clean up LED4 GPIO
   }

   // Set GPIO directions for LEDs
   gpio_direction_output(gpioLED1, ledOn);
   gpio_direction_output(gpioLED2, ledOn);
   gpio_direction_output(gpioLED3, ledOn);
   gpio_direction_output(gpioLED4, ledOn);

   // Configure button GPIO as input
   gpio_direction_input(gpioButton);
   gpio_set_debounce(gpioButton, 30);  // Debounce time for button

   // Request IRQ for the button
   irqNumber = gpio_to_irq(gpioButton);
   result = request_irq(irqNumber, (irq_handler_t) button_handler, IRQF_TRIGGER_RISING, "my_button_handler", NULL);
   if (result < 0) {
      pr_err("Failed to request IRQ for button\n");
      goto r_sysfs_group4;  // Jump to clean up sysfs group for LED4
   }

   INIT_DELAYED_WORK(&my_dwork, my_dwork_func);

   return 0;

r_sysfs_group4:
   sysfs_remove_group(kobj_ref, &attr_group4);
r_gpio_led4:
   gpio_free(gpioLED4);
r_sysfs_group3:
   sysfs_remove_group(kobj_ref, &attr_group3);
r_gpio_led3:
   gpio_free(gpioLED3);
r_sysfs_group2:
   sysfs_remove_group(kobj_ref, &attr_group2);
r_gpio_led2:
   gpio_free(gpioLED2);
r_sysfs_group1:
   sysfs_remove_group(kobj_ref, &attr_group1);
r_gpio_led1:
   gpio_free(gpioLED1);
r_gpio_button:
   gpio_free(gpioButton);
r_kobject:
   kobject_put(kobj_ref);
   return result;
}

static void __exit my_exit(void)
{
    // Free IRQ first
    free_irq(irqNumber, NULL);
    pr_info("IRQ for GPIO %d freed up\n", gpioButton);

    // Unexport GPIOs for the LEDs and button
    gpio_set_value(gpioLED1, 0); // Turn off LED1
    gpio_unexport(gpioLED1);      // Unexport GPIO
    gpio_free(gpioLED1);          // Free the GPIO

    gpio_set_value(gpioLED2, 0); // Turn off LED2
    gpio_unexport(gpioLED2);      // Unexport GPIO
    gpio_free(gpioLED2);          // Free the GPIO

    gpio_set_value(gpioLED3, 0); // Turn off LED3
    gpio_unexport(gpioLED3);      // Unexport GPIO
    gpio_free(gpioLED3);          // Free the GPIO

    gpio_set_value(gpioLED4, 0); // Turn off LED4
    gpio_unexport(gpioLED4);      // Unexport GPIO
    gpio_free(gpioLED4);          // Free the GPIO

    // Free GPIO for the button
    gpio_unexport(gpioButton);    // Unexport GPIO
    gpio_free(gpioButton);        // Free the GPIO
    pr_info("GPIO %d freed up\n", gpioButton);

    // Remove sysfs groups
    sysfs_remove_group(kobj_ref, &attr_group1);
    sysfs_remove_group(kobj_ref, &attr_group2);
    sysfs_remove_group(kobj_ref, &attr_group3);
    sysfs_remove_group(kobj_ref, &attr_group4);
    pr_info("Sysfs groups removed\n");

    // Release the kobject
    kobject_put(kobj_ref);
    pr_info("Kobject released\n");

    // Print the number of button presses detected before exiting
    pr_info("%d button presses were detected!\n", numPresses);
    pr_info("Goodbye from %s!\n", KBUILD_MODNAME);
}


module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("CDAC EDD <edd@cdac.gov.in>");
MODULE_DESCRIPTION("Kernel global delayed workqueue - dynamic example");
