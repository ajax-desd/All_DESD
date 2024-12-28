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
	{ 0x63727adc, "param_ops_ulong" },
	{ 0xceeee77a, "param_array_ops" },
	{ 0x5a4cd130, "param_ops_ushort" },
	{ 0xd544d84d, "param_ops_byte" },
	{ 0xf8da2880, "i2c_del_adapter" },
	{ 0xaf5a1516, "i2c_add_adapter" },
	{ 0x8d49882b, "__dynamic_pr_debug" },
	{ 0xc5850110, "printk" },
	{ 0x81b256c5, "__dynamic_dev_dbg" },
	{ 0x2d6fcc06, "__kmalloc" },
	{ 0x37a0cba, "kfree" },
	{ 0x68f31cbd, "__list_add_valid" },
	{ 0x6ff0c382, "devm_kmalloc" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
};

MODULE_INFO(depends, "");

