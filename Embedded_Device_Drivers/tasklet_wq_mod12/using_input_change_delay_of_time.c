/* Kernel global delayed workqueue - dynamic example */

#define pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#include <linux/init.h>
#include <linux/module.h>
#include <linux/gpio.h>       
#include <linux/kobject.h>   
#include <linux/interrupt.h>
#include <linux/workqueue.h>
#include <linux/delay.h>
	
// button related
static unsigned int gpioButton = 46; // P8_16
static unsigned int irqNumber;	   
static unsigned int n = 5;  // mapped to gpioButton
static unsigned int numPresses = 0;
module_param(n,uint,0644);
MODULE_DESCRIPTION("This is a module that tracks button presses");
static bool ledOn = 0;
static unsigned int gpioLED1 = 60, gpioLED2 = 48,gpioLED3 = 49, gpioLED4 = 47;


// workqueue related
#define MSECS_DELAY	(5000)	     // 5 secs
static struct delayed_work my_dwork;

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
   schedule_delayed_work(&my_dwork, msecs_to_jiffies(n*1000));

   pr_info("Exiting interrupt handler\n");
   
   return (irq_handler_t) IRQ_HANDLED;
}

static int __init my_init(void){
   int result = 0;
   

    pr_info("Setting up IRQ for GPIO %d for button\n", gpioButton);

    if (!gpio_is_valid(gpioButton)) {
        pr_err("Invalid GPIO for button!\n");
        return -ENODEV;
    }

    // Request the GPIO for the button
    result = gpio_request(gpioButton, "sysfs");
    if (result < 0) {
        pr_err("Failed to request GPIO for button\n");
        return result;
    }

    // Request the GPIOs for LEDs
    result = gpio_request(gpioLED1, "sysfs");
    if (result < 0) {
        pr_err("Error in GPIO request for LED1!\n");
        goto r_gpio_req1;
    }

    result = gpio_request(gpioLED2, "sysfs");
    if (result < 0) {
        pr_err("Error in GPIO request for LED2!\n");
        goto r_gpio_req2;
    }
	
    result = gpio_request(gpioLED3, "sysfs");
    if (result < 0) {
        pr_err("Error in GPIO request for LED2!\n");
        goto r_gpio_req3;
    }
    
    result = gpio_request(gpioLED4, "sysfs");
    if (result < 0) {
        pr_err("Error in GPIO request for LED2!\n");
        goto r_gpio_req4;
    }
    // Set GPIO directions for LEDs and button
    gpio_direction_output(gpioLED1, ledOn);
    gpio_direction_output(gpioLED2, ledOn);
    gpio_direction_output(gpioLED3, ledOn);
    gpio_direction_output(gpioLED4, ledOn);

    // Configure button GPIO as input
    gpio_direction_input(gpioButton);
    gpio_set_debounce(gpioButton, 30);  // Debounce time for button
   pr_info("Setting up IRQ for GPIO %d for button\n", gpioButton);

   if (!gpio_is_valid(gpioButton))
   {
      pr_err("Invalid GPIO for button!\n");
      return -ENODEV;
   }

   gpio_request(gpioButton, "sysfs"); 
   gpio_direction_input(gpioButton);  
   irqNumber = gpio_to_irq(gpioButton); 
   pr_info("GPIO %d mapped to IRQ number %d\n", gpioButton, irqNumber);

   gpio_export(gpioButton, false);  		// export in /sys/class/gpio/...

   INIT_DELAYED_WORK(&my_dwork, my_dwork_func);

   result = request_irq(irqNumber, 
		   	(irq_handler_t) button_handler, 
			IRQF_TRIGGER_RISING,
			"my_button_handler",
			NULL);
gpio_export(gpioLED1, false);
    gpio_export(gpioLED2, false);
    gpio_export(gpioLED3, false);
    gpio_export(gpioLED4, false);
    gpio_export(gpioButton, false);
   return result;
    

   

r_gpio_req4:
    gpio_free(gpioLED3);
r_gpio_req3:
    gpio_free(gpioLED2);
r_gpio_req2:
    gpio_free(gpioLED1);
r_gpio_req1:
    gpio_free(gpioButton);
    return result;
}

static void __exit my_exit(void)
{
    gpio_set_value(gpioLED1, 0);
    gpio_unexport(gpioLED1);
    gpio_free(gpioLED1);

    gpio_set_value(gpioLED2, 0);
    gpio_unexport(gpioLED2);
    gpio_free(gpioLED2);

   gpio_set_value(gpioLED3, 0);//
   gpio_unexport(gpioLED3);
   gpio_free(gpioLED3);
   
   gpio_set_value(gpioLED4, 0);//
   gpio_unexport(gpioLED4);
   gpio_free(gpioLED4);     
   free_irq(irqNumber, NULL);
   gpio_unexport(gpioButton);                  
   gpio_free(gpioButton);                      
   pr_info("GPIO %d freed up\n", gpioButton);

   pr_info("%d button presses were detected!\n", numPresses);
   pr_info("Good bye from %s!\n", KBUILD_MODNAME);
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("CDAC EDD <edd@cdac.gov.in>");
MODULE_DESCRIPTION("Kernel global delayed workqueue - dynamic example");
