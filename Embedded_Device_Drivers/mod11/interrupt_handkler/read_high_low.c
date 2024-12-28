#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <linux/init.h>
#include <linux/module.h>
#include <linux/gpio.h>
#include <linux/kobject.h>
#include <linux/interrupt.h>

// Button related
static unsigned int gpioButton = 46;  // P8_16
static unsigned int irqNumber;         // Mapped to gpioButton
static unsigned int numPresses = 0;
static bool ledOn = 0;
static unsigned int gpioLED1 = 60, gpioLED2 = 48;
static struct timer_list my_timer;
// Interrupt handler function
static irqreturn_t button_handler(int irq, void *dev_id)
{
    if (gpio_get_value(gpioButton)) {
        pr_info("Button press interrupt!\n");
        gpio_set_value(gpioLED1, 1);   
        gpio_set_value(gpioLED2, 1);  
    } else {
        pr_info("Button release interrupt!\n");
        gpio_set_value(gpioLED1, 0);   
        gpio_set_value(gpioLED2, 0);
    }

    return IRQ_HANDLED;  // Correct return type
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

    // Set GPIO directions for LEDs and button
    gpio_direction_output(gpioLED1, ledOn);
    gpio_direction_output(gpioLED2, ledOn);

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

    // Export GPIOs
    gpio_export(gpioLED1, false);
    gpio_export(gpioLED2, false);
    gpio_export(gpioButton, false);

    return 0;

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

    free_irq(irqNumber, NULL);

    gpio_unexport(gpioButton);
    gpio_free(gpioButton);

    pr_info("GPIO %d freed up\n", gpioButton);
    pr_info("%d button presses were detected!\n", numPresses);
    pr_info("Goodbye from %s!\n", KBUILD_MODNAME);
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("CDAC EDD <edd@cdac.gov.in>");
MODULE_DESCRIPTION("A simple interrupt driver using GPIO button");

