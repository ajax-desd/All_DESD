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
static unsigned int irqNumber;	     // mapped to gpioButton
static unsigned int numPresses = 0;

// workqueue related
#define MSECS_DELAY	(5000)	     // 5 secs
static struct delayed_work my_dwork;

static void my_dwork_func(struct work_struct *dwork)
{
   numPresses++;
   pr_info("In %s: numPressed = %d\n", __func__, numPresses);
}

static irq_handler_t button_handler(unsigned int irq, void *dev_id, struct pt_regs *regs)
{
   pr_info("In button press interrupt!\n");

   pr_info("Scheduling delayed work...\n");
   schedule_delayed_work(&my_dwork, msecs_to_jiffies(MSECS_DELAY));

   pr_info("Exiting interrupt handler\n");
   
   return (irq_handler_t) IRQ_HANDLED;
}

static int __init my_init(void){
   int result = 0;

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

   return result;
}

static void __exit my_exit(void)
{
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
