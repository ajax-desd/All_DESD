/* My own workqueue - dynamic example */

#define pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#include <linux/init.h>
#include <linux/module.h>
#include <linux/gpio.h>       
#include <linux/kobject.h>   
#include <linux/interrupt.h>
#include <linux/workqueue.h>
#include <linux/random.h>
#include <linux/list.h>
#include <linux/slab.h>
// button related
static unsigned int gpioButton = 46; // P8_16
static unsigned int irqNumber;	     // mapped to gpioButton
static unsigned int numPresses = 0;

// workqueue related
struct my_node{
	char name[9];
	char  status[14];
	char gender[7];
	//char status[]={};
	int id;
	struct list_head my_list;

};



LIST_HEAD(my_head);
static struct workqueue_struct *my_work_queue;
static struct work_struct my_work;
 struct my_node *node,*tmp,*new,*new1,*t;
 
static void my_work_func(struct work_struct *work)
{
    
    pr_info("This is work\n");
    
    unsigned int buf;  // A buffer to store random data
    unsigned int k;    // Variable for the random length of name
    int flag = 1;
    int i;
    char n[9] = "\0";
    char alphabet[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
                         'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
                         'u', 'v', 'w', 'x', 'y', 'z'};
    char *gen[2] = {"Male", "Female"};
    char *sta[2] = {"Contracture", "Permanent"};
    
    // Allocate memory for the node
    node = (struct my_node *)kmalloc(sizeof(struct my_node), GFP_KERNEL);
    if (!node) {
        pr_err("Memory allocation failed\n");
        return;  // Return if memory allocation fails
    }

    // Get a random number
    get_random_bytes(&buf, sizeof(buf));

     while (1) {
        if (k > 3) {
            break;
        }
        k = buf % 8;
    }
   
    // Generate a random name with `k` characters
    for ( i = 0; i < k; i++) {
        n[i] = alphabet[buf % 26];
    }
    n[k] = '\0'; // Null-terminate the string
    
    sprintf(node->name, "%s", n);
  
    sprintf(node->gender, "%s", gen[buf % 2]);

   
    get_random_bytes(&buf, sizeof(buf));  
    sprintf(node->status, "%s", sta[buf % 2]);

    // Initialize the list head and add the node to the list
    INIT_LIST_HEAD(&node->my_list);
    list_add(&node->my_list, &my_head);

    pr_info("name: %s status: %s gender: %s\n", node->name, node->status, node->gender);
    pr_info("In %s: numPresses = %d\n", __func__, numPresses);
}




static irq_handler_t button_handler(unsigned int irq, void *dev_id, struct pt_regs *regs)
{
   pr_info("In button press interrupt!\n");

   pr_info("Scheduling work...\n");
   queue_work(my_work_queue, &my_work);

   pr_info("Exiting interrupt handler\n");
   
   return (irq_handler_t) IRQ_HANDLED;
}



static int __init my_init(void){
   int result = 0;
  
   pr_info("Setting up thread with IRQ for GPIO %d for button\n", gpioButton);

   
   if (!gpio_is_valid(gpioButton))
   {
      pr_err("Invalid GPIO for button!\n");
      return -ENODEV;
   }

   gpio_request(gpioButton, "sysfs"); 
   gpio_direction_input(gpioButton);  
   irqNumber = gpio_to_irq(gpioButton); 
   gpio_set_debounce(gpioButton,30);
   pr_info("GPIO %d mapped to IRQ number %d\n", gpioButton, irqNumber);

   gpio_export(gpioButton, false);  		// export in /sys/class/gpio/...

   my_work_queue = create_workqueue("my_work_queue");
   pr_info("My work queue created!\n");

   INIT_WORK(&my_work, my_work_func);
   
   
   result = request_irq(irqNumber, 
		   	(irq_handler_t) button_handler, 
			IRQF_TRIGGER_RISING,
			"my_button_handler",
			NULL);

   return result;
}

static void __exit my_exit(void)
{
	struct my_node *node1, *tmp1;
	list_for_each_entry(tmp, &my_head, my_list)
	{
		 pr_info("name %s status %s gender %s",node->name,node->status,node->gender);
	}
	list_for_each_entry_safe(node1, tmp1, &my_head, my_list)
	{	// delete the node and free its instantiations
		
		pr_info("Deleting node with ::name %s status %s gender %s\n",node1->name,node1->status,node1->gender);
		list_del(&node1->my_list);
		kfree(node1);
	}
	
   destroy_workqueue(my_work_queue);
   pr_info("Work queue destroyed!\n");

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
MODULE_DESCRIPTION("My own workqueue - dynamic example");

