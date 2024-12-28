/* LED control and blinking via GPIO */

#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <linux/init.h>
#include <linux/module.h>
#include <linux/gpio.h>
#include <linux/kobject.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/mutex.h>
static struct kobject *kobj_ref;
static struct task_struct *task1,*task2;

static unsigned int gpioLED1 = 60, gpioLED2 = 47;

static unsigned int blinkPeriod = 1000; // in milliseconds
module_param(blinkPeriod, uint, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(blinkPeriod, "LED blink period in ms (min=1, default=1000, max=10000)");
static unsigned int blinkPeriod1 = 1000; // in milliseconds
module_param(blinkPeriod1, uint, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(blinkPeriod1, "LED blink period in ms (min=1, default=1000, max=10000)");

struct mutex my_mutex;
static char ledName[10] = {0};
static bool ledOn = 0;
enum modes { OFF, ON, FLASH }; // LED modes
static enum modes mode = FLASH; // default LED mode

// Show function for mode
static ssize_t mode_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    switch (mode) {
        case OFF:   return sprintf(buf, "off\n");
        case ON:    return sprintf(buf, "on\n");
        case FLASH: return sprintf(buf, "flash\n");
        default:    return sprintf(buf, "error\n");
    }
}

// Store function for mode
static ssize_t mode_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
    if (strncmp(buf, "on", count - 1) == 0) {
        mode = ON;
    } else if (strncmp(buf, "off", count - 1) == 0) {
        mode = OFF;
    } else if (strncmp(buf, "flash", count - 1) == 0) {
        mode = FLASH;
    }

    return count;
}

// Show function for blink period
static ssize_t period_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    return sprintf(buf, "%d\n", blinkPeriod);
}
static ssize_t period_show1(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    return sprintf(buf, "%d\n", blinkPeriod1);
}

// Store function for blink period
static ssize_t period_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
    unsigned int period;

    sscanf(buf, "%du", &period);
    if ((period > 1) && (period <= 10000)) {
        blinkPeriod = period;
    }
    pr_info("Period set to %d\n", blinkPeriod);

    return sizeof(period);
}

static ssize_t period_store1(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
    unsigned int period;

    sscanf(buf, "%du", &period);
    if ((period > 1) && (period <= 10000)) {
        blinkPeriod1 = period;
    }
    pr_info("Period set to %d\n", blinkPeriod1);

    return sizeof(period);
}
static struct kobj_attribute period_attr = __ATTR(blinkPeriod, 0664, period_show, period_store);
static struct kobj_attribute mode_attr = __ATTR(mode, 0664, mode_show, mode_store);
static struct kobj_attribute period_attr1 = __ATTR(blinkPeriod1, 0664, period_show1, period_store1);
static struct attribute *led_attrs[] = {
    &period_attr.attr,
    &mode_attr.attr,
    NULL, // sentinel value
};

static struct attribute *led_attrs1[] = {
    &period_attr1.attr,
    &mode_attr.attr,
    NULL, // sentinel value
};

static struct attribute_group attr_group1 = {
    .name = ledName,
    .attrs = led_attrs,
};

static struct attribute_group attr_group2 = {
    .name = ledName,
    .attrs = led_attrs1,
};
// LED flashing thread
static int flash_led1(void *arg)
{
    pr_info("LED flashing thread started with period=%d\n", blinkPeriod);

    while (!kthread_should_stop()) {
    mutex_lock(&my_mutex);
        if (mode == FLASH) {
            ledOn = !ledOn;
            gpio_set_value(gpioLED1, ledOn);
            
        } else { 
            ledOn = false;
            gpio_set_value(gpioLED1, ledOn);
            }

        msleep(blinkPeriod / 2); // 50% duty cycle
        mutex_unlock(&my_mutex);
    }

    pr_info("LED Flashing thread exiting\n");
    return 0;
}
static int flash_led2(void *arg)
{
    pr_info("LED flashing thread started with period=%d\n", blinkPeriod1);

    while (!kthread_should_stop()) {
    mutex_lock(&my_mutex);
        if (mode == FLASH) {
            ledOn = !ledOn;
            gpio_set_value(gpioLED2, ledOn);   
        } else { // OFF
            ledOn = false;
            gpio_set_value(gpioLED2, ledOn);
            //gpio_set_value(gpioLED3, ledOn);
        }

        msleep(blinkPeriod1 / 2); // 50% duty cycle
        mutex_unlock(&my_mutex);
    }

    pr_info("LED Flashing thread exiting\n");
    return 0;
}


// Module initialization
static int __init my_init(void)
{
    int result = 0;
	mutex_init(&my_mutex);
    sprintf(ledName, "led%d", gpioLED1);
    pr_info("Init'ing GPIO LED %s...\n", ledName);

    // Create kobject
    kobj_ref = kobject_create_and_add("cdac_led", kernel_kobj);
    if (!kobj_ref) {
        pr_err("Failed to create kobject\n");
        return -ENOMEM;
    }

    // Create sysfs group
    result = sysfs_create_group(kobj_ref, &attr_group1);
    if (result) {
        pr_err("Failed to create sysfs group\n");
        goto r_sys_grp1;
    }

    // Request and initialize GPIOs
    result = gpio_request(gpioLED1, "sysfs");
    if (result < 0) {
        pr_err("Error in gpio request!\n");
        goto r_gpio_req1;
    }
    sprintf(ledName, "led%d", gpioLED2);
    pr_info("Init'ing GPIO LED %s...\n", ledName);
	result = sysfs_create_group(kobj_ref, &attr_group2);
    if (result) {
        pr_err("Failed to create sysfs group\n");
        goto r_sys_grp2;
    }
    result = gpio_request(gpioLED2, "sysfs");
    if (result < 0) {
        pr_err("Error in gpio request!\n");
        goto r_gpio_req2;
    }
    // Set GPIO direction and export
    ledOn = true;
    gpio_direction_output(gpioLED1, ledOn);
    gpio_export(gpioLED1, false);

    gpio_direction_output(gpioLED2, ledOn);
    gpio_export(gpioLED2, false);


    // Create a kernel thread to handle LED flashing
    task1 = kthread_run(flash_led1, NULL, "LED blink thread");
    if (IS_ERR(task1)) {
        pr_err("Failed to create LED flashing task\n");
        goto r_task1;
    }
   task2 = kthread_run(flash_led2, NULL, "LED blink thread");
    if (IS_ERR(task2)) {
        pr_err("Failed to create LED flashing task\n");
        goto r_task2;
    }
    return 0;

r_task1:
    gpio_set_value(gpioLED1, 0);
    gpio_unexport(gpioLED1);
    gpio_free(gpioLED1);

    gpio_set_value(gpioLED2, 0);
    gpio_unexport(gpioLED2);
    gpio_free(gpioLED2);
    
r_task2:
    gpio_set_value(gpioLED1, 0);
    gpio_unexport(gpioLED1);
    gpio_free(gpioLED1);

    gpio_set_value(gpioLED2, 0);
    gpio_unexport(gpioLED2);
    gpio_free(gpioLED2);
    kthread_stop(task1);
r_gpio_req1:
    sysfs_remove_group(kobj_ref, &attr_group1);
    
r_gpio_req2:
    sysfs_remove_group(kobj_ref, &attr_group1);
    sysfs_remove_group(kobj_ref, &attr_group2);

r_sys_grp2:
    sysfs_remove_group(kobj_ref, &attr_group1);
    kobject_put(kobj_ref);
    return -1;
r_sys_grp1:
    kobject_put(kobj_ref);
    return -1;
}

// Module cleanup
static void __exit my_exit(void)
{
    kthread_stop(task1);
    kthread_stop(task2);

    gpio_set_value(gpioLED1, 0);
    gpio_unexport(gpioLED1);
    gpio_free(gpioLED1);

    gpio_set_value(gpioLED2, 0);
    gpio_unexport(gpioLED2);
    gpio_free(gpioLED2);

    sysfs_remove_group(kobj_ref, &attr_group2);
    sprintf(ledName, "led%d", gpioLED1);
    sysfs_remove_group(kobj_ref, &attr_group1);
    kobject_put(kobj_ref);

    pr_info("Goodbye from %s!\n", KBUILD_MODNAME);
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("CDAC EDD <edd@cdac.gov.in>");
MODULE_DESCRIPTION("A simple LED driver using GPIOs");

