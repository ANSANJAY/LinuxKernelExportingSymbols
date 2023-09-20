#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/jiffies.h>
#include "symbol_test.h"

MODULE_LICENSE("GPL");


static int test_symbol_init(void)
{
    printk(KERN_INFO"%s: In init\ta:%d\te:%c\n", __func__, foo.a, foo.e);
    return 0;
}

static void test_symbol_exit(void)
{
    printk(KERN_INFO"%s: In exit\n", __func__);
}


module_init(test_symbol_init);
module_exit(test_symbol_exit);
