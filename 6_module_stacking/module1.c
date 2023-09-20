#include <linux/kernel.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");

int myadd(int a, int b)
{
    pr_info("%s: Adding %d with %d\t Result:%d\n",
		    __func__, a, b, a+b);
    return a+b;
}

EXPORT_SYMBOL(myadd);

static int module1_init(void)
{
    pr_info("%s: In init\n", __func__);
    return 0;
}

static void module1_exit(void)
{
    pr_info("%s: In exit\n", __func__);
}

module_init(module1_init);
module_exit(module1_exit);
