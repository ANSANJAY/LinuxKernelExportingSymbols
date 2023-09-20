#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/vermagic.h>

static int vermagic_init(void)
{
	pr_info("VERMAGIC_STRING = " VERMAGIC_STRING "\n");
	return 0;
}

static void vermagic_exit(void) {}

module_init(vermagic_init)
module_exit(vermagic_exit)
MODULE_INFO(vermagic, "1234567");
MODULE_LICENSE("GPL");
