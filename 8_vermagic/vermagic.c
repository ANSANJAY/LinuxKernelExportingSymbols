#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/utsname.h>
#define VERMAGIC_STRING "my_vermagic"

static int vermagic_init(void)
{
	pr_info("Kernel version = %s\n", utsname()->release);
	return 0;
}

static void vermagic_exit(void) {}

module_init(vermagic_init)
module_exit(vermagic_exit)
MODULE_LICENSE("GPL");
