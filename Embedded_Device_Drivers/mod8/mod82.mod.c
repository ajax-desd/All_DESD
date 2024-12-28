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
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0x77abe509, "cdev_del" },
	{ 0x5abf8d2b, "class_destroy" },
	{ 0x98171fcf, "device_destroy" },
	{ 0x3066972, "wake_up_process" },
	{ 0x53d95018, "kthread_create_on_node" },
	{ 0x870d5a1c, "__init_swait_queue_head" },
	{ 0x8781d48, "device_create" },
	{ 0xbf451cca, "__class_create" },
	{ 0x83c50091, "cdev_add" },
	{ 0x2f31c9f4, "cdev_init" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0xc37335b0, "complete" },
	{ 0x4fef3ef4, "completion_done" },
	{ 0x952664c5, "do_exit" },
	{ 0xf64bf255, "wait_for_completion" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0xc5850110, "printk" },
};

MODULE_INFO(depends, "");

