#include <linux/module.h>
#include <linux/init.h>

static int __init hello_module_init(void)
{
    printk(KERN_ALERT "Inside the %s function\n", __FUNCTION__);
    return 0;
}

static void __exit hello_module_exit(void)
{
    printk(KERN_ALERT "Inside the %s function\n", __FUNCTION__);
}

module_init(hello_module_init);
module_exit(hello_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Michal Gagos");
MODULE_DESCRIPTION("Hello World driver");
