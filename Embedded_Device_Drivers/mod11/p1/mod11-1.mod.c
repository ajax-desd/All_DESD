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
	{ 0x3c5a8f02, "kthread_stop" },
	{ 0x56c87b84, "kobject_put" },
	{ 0x80ded878, "sysfs_remove_group" },
	{ 0xfe990052, "gpio_free" },
	{ 0x3066972, "wake_up_process" },
	{ 0x53d95018, "kthread_create_on_node" },
	{ 0x47229b5c, "gpio_request" },
	{ 0x71b37f7c, "sysfs_create_group" },
	{ 0x868f8b1f, "kobject_create_and_add" },
	{ 0xb72e3d5f, "gpiod_export" },
	{ 0xb048a0f9, "gpiod_unexport" },
	{ 0xf9a482f9, "msleep" },
	{ 0xb3f7646e, "kthread_should_stop" },
	{ 0x6eb0fe6d, "gpiod_set_raw_value" },
	{ 0x2f129604, "gpiod_direction_output_raw" },
	{ 0xe62ca738, "gpio_to_desc" },
	{ 0x8f678b07, "__stack_chk_guard" },
	{ 0x86332725, "__stack_chk_fail" },
	{ 0xc5850110, "printk" },
	{ 0xbcab6ee6, "sscanf" },
	{ 0x84b183ae, "strncmp" },
	{ 0x3c3ff9fd, "sprintf" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
};

MODULE_INFO(depends, "");

