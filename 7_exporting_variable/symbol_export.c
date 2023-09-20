#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/jiffies.h>
#include "symbol_test.h"

MODULE_LICENSE("GPL");

struct test foo;
EXPORT_SYMBOL(foo);



static int test_export_init(void)
{
	foo.a = 5;
	foo.b = 6;
	foo.c = 7;
	foo.d = 8;
	foo.e = '9';
    printk(KERN_INFO"%s: In init\n", __func__);
    return 0;
}

static void test_export_exit(void)
{
    printk(KERN_INFO"%s: In exit\n", __func__);
}


module_init(test_export_init);
module_exit(test_export_exit);
