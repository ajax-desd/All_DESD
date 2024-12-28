/* Kernel linked list - dynamic nodes, node replacement */

#define pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/list.h>

// number of nodes in the kernel linked list
#define NUM_NODES	(10)

// linked list node definition
struct my_node
{
	int data;
	struct list_head my_list;
};

static int x=10;
static int d=5;
static int k=NUM_NODES;
module_param(k, int, S_IRUGO | S_IWUSR);
module_param(x, int, S_IRUGO | S_IWUSR);
module_param(d, int, S_IRUGO | S_IWUSR); 

LIST_HEAD(my_head);

static int __init my_mod_init(void)
{
	int count, data=x;
	struct my_node *node, *tmp;
	//struct my_node *t;

	pr_info("Hello world from %s!\n", KBUILD_MODNAME);
	
	
	// create nodes dynamically via option #3
	for (count=1;count<=k;count++)
	{
		// kmalloc node
		
		node = (struct my_node *)kmalloc(sizeof(struct my_node), GFP_KERNEL);
		node->data = data;
		// enable its 'linked list state'
		INIT_LIST_HEAD(&node->my_list);
		// add node
		list_add(&node->my_list, &my_head);
		data = x+(count)*d;
		
	}
	
	// forward traversal
	pr_info("Linked list forwards:\n");
	count  = 0;
	list_for_each_entry(tmp, &my_head, my_list)
	{
		pr_info("Node %d, data=%d\n", count++, tmp->data);
	}
	
	

	return 0;
}

static void __exit my_mod_exit(void)
{
	struct my_node *node, *tmp;

	list_for_each_entry_safe(node, tmp, &my_head, my_list)
	{	// delete the node and free its instantiations
		pr_info("Deleting node with data=%d\n", node->data);
		list_del(&node->my_list);
		kfree(node);
	}
	pr_info("Goodbye world from %s!\n", KBUILD_MODNAME);

	return;
}

module_init(my_mod_init);
module_exit(my_mod_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("EDD <edd@cdac.gov.in>");
MODULE_DESCRIPTION("Kernel linked list - dynamic nodes, node replacement!");
