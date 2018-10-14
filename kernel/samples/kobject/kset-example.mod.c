#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xbff2abe1, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x3d04bdc3, __VMLINUX_SYMBOL_STR(kset_unregister) },
	{ 0xa61de15c, __VMLINUX_SYMBOL_STR(kset_create_and_add) },
	{ 0x3bfcedd5, __VMLINUX_SYMBOL_STR(kernel_kobj) },
	{ 0xd1f8e25e, __VMLINUX_SYMBOL_STR(kobject_uevent) },
	{ 0xde98c647, __VMLINUX_SYMBOL_STR(kobject_put) },
	{ 0x2adb5b4f, __VMLINUX_SYMBOL_STR(kobject_init_and_add) },
	{ 0xdf3deb56, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x74cf6b1f, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0x20c55ae0, __VMLINUX_SYMBOL_STR(sscanf) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "EE4106B3CE7B2B66B1DE091");
