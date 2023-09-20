#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/jiffies.h>

MODULE_LICENSE("GPL");

void print_jiffies(void)
{
    printk(KERN_INFO"%s: Jiffies:%ld\n",__func__, jiffies);
}

static int test_export_init(void)
{
    printk(KERN_INFO"%s: In init\n", __func__);
    return 0;
}

static void test_export_exit(void)
{
    printk(KERN_INFO"%s: In exit\n", __func__);
}

EXPORT_SYMBOL_GPL(print_jiffies);

module_init(test_export_init);
module_exit(test_export_exit);
