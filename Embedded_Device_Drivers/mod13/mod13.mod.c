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
	{ 0xe024bc26, "i2c_del_driver" },
	{ 0xbe217956, "i2c_unregister_device" },
	{ 0x159bc1e2, "i2c_put_adapter" },
	{ 0xf38ed13a, "i2c_register_driver" },
	{ 0x69fc903a, "i2c_new_client_device" },
	{ 0x2ec30375, "i2c_get_adapter" },
	{ 0xe1cdc1a3, "i2c_smbus_read_byte_data" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0xc5850110, "printk" },
};

MODULE_INFO(depends, "");

MODULE_ALIAS("i2c:my_i2c_stub");
