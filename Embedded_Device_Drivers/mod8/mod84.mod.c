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
	{ 0x37a0cba, "kfree" },
	{ 0x8f678b07, "__stack_chk_guard" },
	{ 0x86332725, "__stack_chk_fail" },
	{ 0x3c5a8f02, "kthread_stop" },
	{ 0x3066972, "wake_up_process" },
	{ 0x53d95018, "kthread_create_on_node" },
	{ 0x3c3ff9fd, "sprintf" },
	{ 0xfe2e64c4, "kmem_cache_alloc_trace" },
	{ 0x8335c0f7, "kmalloc_caches" },
	{ 0xe346f67a, "__mutex_init" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0x67ea780, "mutex_unlock" },
	{ 0xc5850110, "printk" },
	{ 0xc271c3be, "mutex_lock" },
	{ 0xb3f7646e, "kthread_should_stop" },
	{ 0xf9a482f9, "msleep" },
	{ 0xff178f6, "__aeabi_idivmod" },
};

MODULE_INFO(depends, "");

