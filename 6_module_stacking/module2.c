#include <linux/kernel.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");

extern int myadd(int a, int b);


static int module2_init(void)
{
    pr_info("%s: In init\n", __func__);
    pr_info("%s: Add:%d\n", __func__, myadd(3, 5));
    return 0;
}

static void module2_exit(void)
{
    pr_info("%s: In exit\n", __func__);
}

module_init(module2_init);
module_exit(module2_exit);
