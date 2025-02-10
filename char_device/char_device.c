#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/fs.h>

#define DEV_NAME "char_device"
#define MAX_DEV 2

// Device data holder. Can be expanded with additional data.
struct my_char_device_data {
    struct cdev cdev;
};

static int major = 0;                                       // Major device number
static struct class *mychardev_class = NULL;                // Sysfs class
static struct mychar_device_data mychardev_data[MAX_DEV];   // Array of data for each device

static int __init char_device_init(void)
{
    int err, i;
    dev_t dev;

    err = alloc_chrdev_region(&dev, 0, MAX_DEV, DEV_NAME);

    dev_major = MAJOR(dev);

    return 0;
}

static void __exit char_device_exit(void)
{
    unregister_chrdev(major, "char_dev");
}

/**
 * Metadata
 */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Michal Gagos");
MODULE_DESCRIPTION("A driver that registers a character device");

module_init(char_device_init);
module_exit(char_device_exit);