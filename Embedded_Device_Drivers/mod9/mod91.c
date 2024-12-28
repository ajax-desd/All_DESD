/* Kernel linked list - static nodes */

#define pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/list.h>

/* linked list node definition
struct my_node
{
	int data;
	struct list_head my_list;
};

//struct my_node node2;
// create list head pointer/node
LIST_HEAD(my_head);

static int __init my_mod_init(void)
{
	int count = 0;
	struct my_node *tmp;
	int i;
	pr_info("Hello world from %s!\n", KBUILD_MODNAME);
	
	// create node1 using option #1
	/*struct my_node node1  = 
	{
		.data=10,
		.my_list = LIST_HEAD_INIT(node1.my_list)
	};
	// add node1
	list_add(&node1.my_list, &my_head);

	// create node2 using option #2
	struct my_node node2;
	node2.data = 20;
	INIT_LIST_HEAD(&node2.my_list);
	// add node2
	list_add(&node2.my_list, &my_head);
	
	
	struct my_node node3;
	node3.data = 30;
	INIT_LIST_HEAD(&node3.mylist);
	list_add(&node3.my_list,&my_head);
	
	
	struct my_node node4={
		.data=40;
		
	}
	*/
//option 1
    /*struct my_node node[5];
    for (i = 0; i < 5; i++) {
        node[i].data = i * 10;  // Assign data to the node
        INIT_LIST_HEAD(&node[i].my_list);  // Initialize each node's list head
        list_add(&node[i].my_list, &my_head);  // Add node's list to my_head
    }

    // Traverse the list and print the data of each node
    list_for_each_entry(tmp, &my_head, my_list) {
        pr_info("Node %d, data=%d\n", count++, tmp->data);
    }
    
    */
//option 2
/*	struct my_node node1  = 
	{
		.data=10,
		.my_list = LIST_HEAD_INIT(node1.my_list)
	};
	
	struct my_node node[5]={
	    for (i = 0; i < 5; i++) {
		.data[i] = i * 10;  // Assign data to the node
		INIT_LIST_HEAD(&node[i].my_list);  // Initialize each node's list head
		list_add(&node[i].my_list, &my_head);  // Add node's list to my_head
	    }
	    };

    // Traverse the list and print the data of each node
    list_for_each_entry(tmp, &my_head, my_list) {
        pr_info("Node %d, data=%d\n", count++, tmp->data);
    }
    
    

	return 0;
}

static void __exit my_mod_exit(void)
{
	pr_info("Goodbye world from %s!\n", KBUILD_MODNAME);

	return;
}

module_init(my_mod_init);
module_exit(my_mod_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("EDD <edd@cdac.gov.in>");
MODULE_DESCRIPTION("Kernel linked list - static nodes!");*/
