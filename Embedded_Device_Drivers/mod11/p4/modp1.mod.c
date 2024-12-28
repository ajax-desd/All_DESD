#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0x3726c6aa, "module_layout" },
	{ 0x15f5c1f6, "param_ops_uint" },
	{ 0x2b68bd2f, "del_timer" },
	{ 0x98171fcf, "device_destroy" },
	{ 0x3c5a8f02, "kthread_stop" },
	{ 0x37a0cba, "kfree" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0x77abe509, "cdev_del" },
	{ 0x56c87b84, "kobject_put" },
	{ 0x80ded878, "sysfs_remove_group" },
	{ 0xc6f46339, "init_timer_key" },
	{ 0xfe990052, "gpio_free" },
	{ 0x3066972, "wake_up_process" },
	{ 0x53d95018, "kthread_create_on_node" },
	{ 0x47229b5c, "gpio_request" },
	{ 0x71b37f7c, "sysfs_create_group" },
	{ 0x868f8b1f, "kobject_create_and_add" },
	{ 0x5abf8d2b, "class_destroy" },
	{ 0x8781d48, "device_create" },
	{ 0xbf451cca, "__class_create" },
	{ 0x83c50091, "cdev_add" },
	{ 0x2f31c9f4, "cdev_init" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0xfe2e64c4, "kmem_cache_alloc_trace" },
	{ 0x8335c0f7, "kmalloc_caches" },
	{ 0x5f754e5a, "memset" },
	{ 0xae353d77, "arm_copy_from_user" },
	{ 0xb72e3d5f, "gpiod_export" },
	{ 0xb048a0f9, "gpiod_unexport" },
	{ 0xb3f7646e, "kthread_should_stop" },
	{ 0x6eb0fe6d, "gpiod_set_raw_value" },
	{ 0x2f129604, "gpiod_direction_output_raw" },
	{ 0xe62ca738, "gpio_to_desc" },
	{ 0x51a910c0, "arm_copy_to_user" },
	{ 0x88db9f48, "__check_object_size" },
	{ 0x2cfde9a2, "warn_slowpath_fmt" },
	{ 0x8f678b07, "__stack_chk_guard" },
	{ 0x86332725, "__stack_chk_fail" },
	{ 0xbcab6ee6, "sscanf" },
	{ 0x84b183ae, "strncmp" },
	{ 0x3c3ff9fd, "sprintf" },
	{ 0xc38c83b8, "mod_timer" },
	{ 0x526c3a6c, "jiffies" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0xc5850110, "printk" },
};

MODULE_INFO(depends, "");

