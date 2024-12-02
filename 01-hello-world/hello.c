#include <linux/module.h>
#include <linux/init.h>

/**
 * __init tells the compiler to ignore the function being unused
 * It also places it in the .init.text section so that it can be discarded after being run
 */
static int __init hello_module_init(void)
{
    /* Printk prints the string to the kernel logs */
    /* We can see what was printed in dmesg */
    printk(KERN_ALERT "Inside the %s function\n", __FUNCTION__);
    return 0;
}

static void __exit hello_module_exit(void)
{
    printk(KERN_ALERT "Inside the %s function\n", __FUNCTION__);
}

module_init(hello_module_init); /* Runs the provided function on insmod */
module_exit(hello_module_exit); /* Runs the provided function on rmmod */

/* Metadata about the module */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Michal Gagos");
MODULE_DESCRIPTION("Hello World driver");
