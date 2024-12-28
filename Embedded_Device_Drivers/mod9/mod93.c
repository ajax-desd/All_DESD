
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/err.h>
#include <linux/device.h>
#include <linux/kdev_t.h>
#include <linux/cdev.h>
#include <linux/ioctl.h>
#include <linux/slab.h>
#include <linux/list.h>
#include <linux/uaccess.h> // For copy_from_user

#include "my_ioctls.h" // IOCTL command definitions

#define MY_CLASS_NAME "cdac_cls"
#define MY_DEV_NAME "cdac_dev"
#define MY_KBUF_SZ (1024)
#define NUM_NODES (50)  // Maximum number of nodes
#define MAX_NAME_LEN (10)
#define MAX_STATUS_LEN (15)

LIST_HEAD(my_head);  // Head of the linked list
dev_t dev = 0;
static struct class *dev_class;
static struct device *cdevice;
static struct cdev my_cdev;

struct my_node {
    char name[MAX_NAME_LEN];
    unsigned long id;
    char sex[10];  // 'sex' as string
    char status[MAX_STATUS_LEN];
    struct list_head my_list; // Link to next node in list
};

struct my_node *node, *tmp;  // Temporary pointers for list traversal

// IOCTL functions
static int my_open(struct inode *inode, struct file *file);
static ssize_t my_read(struct file *file, char __user *buf, size_t len, loff_t *off);
static ssize_t my_write(struct file *file, const char __user *buf, size_t len, loff_t *off);
static long my_ioctl(struct file *file, unsigned int cmd, unsigned long args);
static int my_release(struct inode *inode, struct file *file);

// File operations struct
static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = my_open,
    .read = my_read,
    .write = my_write,
    .unlocked_ioctl = my_ioctl,
    .release = my_release,
};

// Kernel module initialization
static int __init my_mod_init(void)
{
    int ans;

    ans = alloc_chrdev_region(&dev, 0, 1, MY_DEV_NAME); // Allocate char device region
    if (ans < 0) {
        pr_err("Error in major:minor allotment!\n");
        return -1;
    }
    pr_info("major:minor %d:%d allotted!\n", MAJOR(dev), MINOR(dev));

    // Initialize cdev
    cdev_init(&my_cdev, &fops);

    ans = cdev_add(&my_cdev, dev, 1);
    if (ans < 0) {
        pr_err("Could not add cdev to kernel!\n");
        goto r_cdev;
    }

    dev_class = class_create(THIS_MODULE, MY_CLASS_NAME);
    if (IS_ERR(dev_class)) {
        pr_err("Could not create device class %s\n", MY_CLASS_NAME);
        goto r_class;
    }

    cdevice = device_create(dev_class, NULL, dev, NULL, MY_DEV_NAME);
    if (IS_ERR(cdevice)) {
        pr_err("Could not create device %s\n", MY_DEV_NAME);
        goto r_device;
    }
    pr_info("Device %s under class %s created successfully\n", MY_DEV_NAME, MY_CLASS_NAME);
    return 0;

r_device:
    class_destroy(dev_class);
r_class:
    cdev_del(&my_cdev);
r_cdev:
    unregister_chrdev_region(dev, 1);
    return -1;
}

// Kernel module exit function
static void __exit my_mod_exit(void)
{
    int count = 0;
    // Clean up linked list
    list_for_each_entry_safe(node, tmp, &my_head, my_list) {
        pr_info("Node %d: name=%s, sex=%s, status=%s, id=%ld\n", count, node->name, node->sex, node->status, node->id);
        count++;
        list_del(&node->my_list);
        kfree(node); // Free memory for the node
    }

    pr_info("Goodbye world from %s!\n", KBUILD_MODNAME);
    device_destroy(dev_class, dev);
    class_destroy(dev_class);
    cdev_del(&my_cdev);
    unregister_chrdev_region(dev, 1);
}

// Write function - for adding records to the list
static ssize_t my_write(struct file *file, const char __user *buf, size_t len, loff_t *off)
{
    char *tmp_buf;
    struct my_node *node;
    char *token;

    pr_info("My write function %s called\n", __func__);

    tmp_buf = kmalloc(len + 1, GFP_KERNEL);
    if (!tmp_buf) {
        pr_err("Error allocating temporary buffer\n");
        return -ENOMEM;
    }

    if (copy_from_user(tmp_buf, buf, len)) {
        pr_err("Error in data read from user space\n");
        kfree(tmp_buf);
        return -EFAULT;
    }

    tmp_buf[len] = '\0'; // Ensure null-terminated string

    // Parsing the incoming buffer
    while ((token = strsep(&tmp_buf, ",")) != NULL) {
        if (token[0] == '\0') continue; // Skip empty tokens

        node = kmalloc(sizeof(struct my_node), GFP_KERNEL);
        if (!node) {
            pr_err("Memory allocation failed for node\n");
            kfree(tmp_buf);
            return -ENOMEM;
        }

        // Fill the node with data
        strncpy(node->name, token, sizeof(node->name) - 1);
        token = strsep(&tmp_buf, ",");
        strncpy(node->sex, token, sizeof(node->sex) - 1);
        token = strsep(&tmp_buf, ",");
        strncpy(node->status, token, sizeof(node->status) - 1);
        token = strsep(&tmp_buf, ",");
        node->id = simple_strtoul(token, NULL, 10);

        // Add the node to the list
        INIT_LIST_HEAD(&node->my_list);
        list_add(&node->my_list, &my_head);
    }

    kfree(tmp_buf);
    return len;
}

// IOCTL function - Handles SHOW_LIST and DEL_LIST commands
static long my_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    int count;
    switch (cmd) {
        case DEL_LIST:
            count = 0;
            list_for_each_entry_safe(node, tmp, &my_head, my_list) {
                pr_info("Node %d: name=%s, sex=%s, status=%s, id=%ld\n", count, node->name, node->sex, node->status, node->id);
                count++;
                list_del(&node->my_list);
                kfree(node);
            }
            break;

        case SHOW_LIST:
            pr_info("Linked list contents:\n");
            count = 0;
            list_for_each_entry(node, &my_head, my_list) {
                pr_info("Node %d: name=%s, sex=%s, status=%s, id=%ld\n", count, node->name, node->sex, node->status, node->id);
                count++;
            }
            break;

        default:
            pr_err("Invalid IOCTL command\n");
            break;
    }
    return 0;
}

static int my_open(struct inode *inode, struct file *file)
{
    pr_info("My open function %s called\n", __func__);
    return 0;
}

static int my_release(struct inode *inode, struct file *file)
{
    pr_info("My release function %s called\n", __func__);
    return 0;
}

module_init(my_mod_init);
module_exit(my_mod_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("CDAC");
MODULE_DESCRIPTION("Kernel module for managing employee records using linked list and IOCTL");


