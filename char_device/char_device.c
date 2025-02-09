#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>

static int major;   // Major device number

/**
 * fops functions
 */
static ssize_t custom_read(struct file *file, char __user *user, size_t len, loff_t *o) {
    printk("char_dev - Read was called\n");
}

/**
 * fops defines what the device does when certain actions are used on it
 */
static struct file_operations fops = {
    .read = custom_read,
};

static int __init char_device_init(void)
{
    // Allocate a device number
    major = register_chrdev(0, "char_dev", &fops);

    if (major < 0) {
        printk("char_dev - Error registering chrdev\n");
        return major;
    }

    printk("char_dev - Registered at Major Device Number: %d\n", major);

    return 0;
}

static void __exit char_device_exit(void)
{
    unregister_chrdev(major, "char_dev");
}

module_init(char_device_init);
module_exit(char_device_exit);


/**
 * Metadata
 */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Michal Gagos");
MODULE_DESCRIPTION("A driver that registers a character device");
