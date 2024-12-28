#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <linux/init.h>
#include <linux/module.h>
#include <linux/gpio.h>
#include <linux/kobject.h>
#include <linux/interrupt.h>
#include <linux/timer.h>
#include <linux/jiffies.h>
// Button related
static unsigned int gpioButton = 46;  // P8_16
static unsigned int irqNumber;         // Mapped to gpioButton
static unsigned int num = 0;
static bool ledOn = 0;
static unsigned int gpioLED1 = 60, gpioLED2 = 48,gpioLED3 = 49, gpioLED4 = 47;
static struct timer_list my_timer;
// Interrupt handler function

#define TIME_INTVL	(1000)	// milliseconds
static irqreturn_t button_handler(int irq, void *dev_id)
{
    //if(flag=1){
        pr_info("Button press interrupt!\n");
        gpio_set_value(gpioLED1, (num & 0x01));   
        gpio_set_value(gpioLED2, (num & 0x02));  
        gpio_set_value(gpioLED3, (num & 0x04));   
        gpio_set_value(gpioLED4, (num & 0x08)); 
    

    return IRQ_HANDLED;  // Correct return type
}


void my_timer_cb(struct timer_list *tmr)
{
	int ctx = in_interrupt();
	pr_info("In timer, count=[%d], running in %s context\n", num,
			(ctx==0?"kernel":"interrupt") );
	if(gpio_get_value(gpioButton))
	{	
		//button_handler(int irq, void *dev_id)
		gpio_set_value(gpioLED1, (num & 0x01));   
        	gpio_set_value(gpioLED2, (num & 0x02));  
        	gpio_set_value(gpioLED3, (num & 0x04));   
        	gpio_set_value(gpioLED4, (num & 0x08)); 
		if(num==15)
		{num=0;}
		else{ num++;}
	}
	else {
		gpio_set_value(gpioLED1, (num & 0x01));   
        	gpio_set_value(gpioLED2, (num & 0x02));  
       	 	gpio_set_value(gpioLED3, (num & 0x04));   
        	gpio_set_value(gpioLED4, (num & 0x08)); 
		if(num==0)
		{num=15;}
		else{ num--;}
	}
	// reload timer with same data - to ensure regular timer start-expiry
	mod_timer(&my_timer, jiffies + msecs_to_jiffies(TIME_INTVL));
	
	return;
}

static int __init my_init(void)
{
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

    // Map GPIO to IRQ
    irqNumber = gpio_to_irq(gpioButton);
    pr_info("GPIO %d mapped to IRQ number %d\n", gpioButton, irqNumber);

    // Request IRQ for the button press with rising and falling edge triggers
    result = request_irq(irqNumber,
                         button_handler,
                         IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING,
                         "my_button_handler",
                         NULL);
    if (result < 0) {
        pr_err("Failed to request IRQ\n");
        goto r_gpio_req3;
    }
	
	
	timer_setup(&my_timer, my_timer_cb, 0);
	mod_timer(&my_timer, jiffies + msecs_to_jiffies(TIME_INTVL));
	pr_info("Kernel timer created!\n");
    // Export GPIOs
    gpio_export(gpioLED1, false);
    gpio_export(gpioLED2, false);
    gpio_export(gpioLED3, false);
    gpio_export(gpioLED4, false);
    gpio_export(gpioButton, false);

    return 0;

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
    // Cleanup
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
   del_timer(&my_timer);
    pr_info("GPIO %d freed up\n", gpioButton);
    pr_info("%d button presses were detected!\n", num);
    pr_info("Goodbye from %s!\n", KBUILD_MODNAME);
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("CDAC EDD <edd@cdac.gov.in>");
MODULE_DESCRIPTION("A simple interrupt driver using GPIO button");

