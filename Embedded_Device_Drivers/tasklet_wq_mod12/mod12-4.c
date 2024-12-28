#define pr_fmt(fmt)	KBUILD_MODNAME ": " fmt
//additinolay use notify on set  + module call backj
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
static unsigned int n1 = 5, n2 = 5, n3 = 5, n4 = 5;  
static unsigned int numPresses = 0;
module_param(n1, uint, 0644);
MODULE_DESCRIPTION("n1 for led1");
module_param(n2, uint, 0644);
MODULE_DESCRIPTION("n2 for led2");
module_param(n3, uint, 0644);
MODULE_DESCRIPTION("n3 for led3");
module_param(n4, uint, 0644);
MODULE_DESCRIPTION("n4 for led4");

static bool ledOn = 0;
static unsigned int gpioLED1 = 60, gpioLED2 = 48, gpioLED3 = 49, gpioLED4 = 47;
static char ledName[10] = {0};

// workqueue related
#define MSECS_DELAY	(5000)	     // 5 secs
static struct delayed_work my_dwork1, my_dwork2, my_dwork3, my_dwork4;

static ssize_t mode_show1(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    return sprintf(buf, "%d\n", n1);
}

static ssize_t mode_store1(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
    unsigned int period;                    
    sscanf(buf, "%du", &period);             
    if ((period >= 0) && (period <= 15)) {        
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
    if ((period >= 0) && (period <= 15)) {        
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
    if ((period >= 0) && (period <= 15)) {        
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
    if ((period >= 0) && (period <= 15)) {        
        n4 = period;                 
    }
    pr_info("Period set to %d\n", n4);
    return sizeof(period);
}

static struct kobj_attribute mode_attr1 = __ATTR(n1, 0664, mode_show1, mode_store1);
static struct kobj_attribute mode_attr2 = __ATTR(n2, 0664, mode_show2, mode_store2);
static struct kobj_attribute mode_attr3 = __ATTR(n3, 0664, mode_show3, mode_store3);
static struct kobj_attribute mode_attr4 = __ATTR(n4, 0664, mode_show4, mode_store4);

// Define attribute groups
static struct attribute *led_attrs1[] = { &mode_attr1.attr, NULL };
static struct attribute *led_attrs2[] = { &mode_attr2.attr, NULL };
static struct attribute *led_attrs3[] = { &mode_attr3.attr, NULL };
static struct attribute *led_attrs4[] = { &mode_attr4.attr, NULL };

static struct attribute_group attr_group1 = {
    .name = "led1",               
    .attrs = led_attrs1,                      
};

static struct attribute_group attr_group2 = {
    .name = "led2",               
    .attrs = led_attrs2,                      
};

static struct attribute_group attr_group3 = {
    .name = "led3",               
    .attrs = led_attrs3,                      
};

static struct attribute_group attr_group4 = {
    .name = "led4",               
    .attrs = led_attrs4,                      
};

// Workqueue related function
static void my_dwork_func1(struct work_struct *dwork)
{
    numPresses++;
    pr_info("Button press interrupt!\n");
    
    gpio_set_value(gpioLED1, 1);   
    

}
static void my_dwork_func2(struct work_struct *dwork)
{
    numPresses++;
    pr_info("Button press interrupt!\n");

    gpio_set_value(gpioLED2,1);  
    
}
static void my_dwork_func3(struct work_struct *dwork)
{
    numPresses++;
    pr_info("Button press interrupt!\n");
    
    gpio_set_value(gpioLED3,1);   
    
}
static void my_dwork_func4(struct work_struct *dwork)
{
    numPresses++;
    pr_info("Button press interrupt!\n");
    
    gpio_set_value(gpioLED4, 1); 

}
static irq_handler_t button_handler(unsigned int irq, void *dev_id, struct pt_regs *regs)
{
    pr_info("In button press interrupt!\n");
    pr_info("Scheduling delayed work...\n");
    
    if(gpio_get_value(gpioButton)){
    gpio_set_value(gpioLED4, 0); gpio_set_value(gpioLED3, 0); 
    gpio_set_value(gpioLED2, 0); 
    gpio_set_value(gpioLED1, 0); 
    }else{
    schedule_delayed_work(&my_dwork1, msecs_to_jiffies(n1*1000));
        schedule_delayed_work(&my_dwork2, msecs_to_jiffies(n2*1000));
            schedule_delayed_work(&my_dwork3, msecs_to_jiffies(n3*1000));
                schedule_delayed_work(&my_dwork4, msecs_to_jiffies(n4*1000));
    }
    
    pr_info("Exiting interrupt handler\n");
    return (irq_handler_t) IRQ_HANDLED;
}

static int __init my_init(void)
{
    int result = 0;
    
    // Create the kobject
    kobj_ref = kobject_create_and_add("cdac_led", NULL); 
    if (!kobj_ref) {
        pr_err("Failed to create kobject\n");
        return -ENOMEM;
    }

    pr_info("Setting up IRQ for GPIO %d for button\n", gpioButton);

    // Request the GPIO for the button
    if (!gpio_is_valid(gpioButton)) {
        pr_err("Invalid GPIO for button!\n");
        result = -ENODEV;
        goto r_kobject;
    }

    result = gpio_request(gpioButton, "sysfs");
    if (result < 0) {
        pr_err("Failed to request GPIO for button\n");
        goto r_kobject;
    }

    // Request and set up the LEDs and sysfs groups
    result = gpio_request(gpioLED1, "sysfs");
    if (result < 0) {
        pr_err("Failed to request GPIO for LED1\n");
        goto r_gpio_button;
    }

    result = sysfs_create_group(kobj_ref, &attr_group1);
    if (result) {
        pr_err("Failed to create sysfs group for LED1\n");
        goto r_gpio_led1;
    }

    result = gpio_request(gpioLED2, "sysfs");
    if (result < 0) {
        pr_err("Failed to request GPIO for LED2\n");
        goto r_sysfs_group1;
    }

    result = sysfs_create_group(kobj_ref, &attr_group2);
    if (result) {
        pr_err("Failed to create sysfs group for LED2\n");
        goto r_gpio_led2;
    }

    result = gpio_request(gpioLED3, "sysfs");
    if (result < 0) {
        pr_err("Failed to request GPIO for LED3\n");
        goto r_sysfs_group2;
    }

    result = sysfs_create_group(kobj_ref, &attr_group3);
    if (result) {
        pr_err("Failed to create sysfs group for LED3\n");
        goto r_gpio_led3;
    }

    result = gpio_request(gpioLED4, "sysfs");
    if (result < 0) {
        pr_err("Failed to request GPIO for LED4\n");
        goto r_sysfs_group3;
    }

    result = sysfs_create_group(kobj_ref, &attr_group4);
    if (result) {
        pr_err("Failed to create sysfs group for LED4\n");
        goto r_gpio_led4;
    }

    // Set GPIO directions for LEDs
    gpio_direction_output(gpioLED1, ledOn);
    gpio_direction_output(gpioLED2, ledOn);
    gpio_direction_output(gpioLED3, ledOn);
    gpio_direction_output(gpioLED4, ledOn);

    // Configure button GPIO as input
    gpio_direction_input(gpioButton);
    gpio_set_debounce(gpioButton, 30);  

    // Request IRQ for the button
    irqNumber = gpio_to_irq(gpioButton);
    result = request_irq(irqNumber, (irq_handler_t) button_handler, IRQF_TRIGGER_RISING|IRQF_TRIGGER_FALLING, "my_button_handler", NULL);
    if (result < 0) {
        pr_err("Failed to request IRQ for button\n");
        goto r_sysfs_group4;
    }

    INIT_DELAYED_WORK(&my_dwork1, my_dwork_func1);
    INIT_DELAYED_WORK(&my_dwork2, my_dwork_func2);
    INIT_DELAYED_WORK(&my_dwork3, my_dwork_func3);
    INIT_DELAYED_WORK(&my_dwork4, my_dwork_func4);
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


    gpio_set_value(gpioLED1, 0); 
    gpio_unexport(gpioLED1);      
    gpio_free(gpioLED1);          

    gpio_set_value(gpioLED2, 0); 
    gpio_unexport(gpioLED2);      
    gpio_free(gpioLED2);         

    gpio_set_value(gpioLED3, 0); 
    gpio_unexport(gpioLED3);     
    gpio_free(gpioLED3);          

    gpio_set_value(gpioLED4, 0); 
    gpio_unexport(gpioLED4);     
    gpio_free(gpioLED4);         
    
    gpio_unexport(gpioButton);    
    gpio_free(gpioButton);        
    pr_info("GPIO %d freed up\n", gpioButton);

    sysfs_remove_group(kobj_ref, &attr_group1);
    sysfs_remove_group(kobj_ref, &attr_group2);
    sysfs_remove_group(kobj_ref, &attr_group3);
    sysfs_remove_group(kobj_ref, &attr_group4);
    pr_info("Sysfs groups removed\n");

    kobject_put(kobj_ref);
    pr_info("Kobject released\n");

    pr_info("%d button presses were detected!\n", numPresses);
    pr_info("Goodbye from %s!\n", KBUILD_MODNAME);
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("CDAC EDD <edd@cdac.gov.in>");
MODULE_DESCRIPTION("Kernel global delayed workqueue - dynamic example");

