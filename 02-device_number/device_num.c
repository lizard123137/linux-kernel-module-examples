#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h> /* fs.h is needed for device file creation */

/**
 * WARNING
 * Currently this driver doesn't compile. I'll fix it later...
 */


/* Function prototypes */
static int device_file_open(struct inode *device_file, struct file *instance);
static int device_file_close(struct inode *device_file, struct file *instance);

/* Variables for device and device class */
static dev_t device_number;
static struct class *device_class;
static struct cdev device;

/**
 * This structure informs the kernel about all the necessary operations that
 * the device file will be able to perform
 */
static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = device_file_open,
    .release = device_file_close,
};

static int __init device_module_init(void)
{
    /* Allocate a device number */
    if (alloc_chrdev_region(&device_number, 0, 1, "driver-name") < 0) {
        printk(KERN_ERR "Device nr. could not be allocated\n");
        return -1;
    }

    printk(KERN_INFO "Device Major: %d, Minor: %d was registered\n", MAJOR(device_number), MINOR(device_number));

    /* Create device class */
    device_class = class_create("device-class");

    if (device_class == NULL) {
        printk(KERN_ERR "Device class can not be created!\n");
        goto class_error;
    }

    /* Create device file */
    if (device_create(&device, NULL, device_number, NULL, "driver-name") == NULL) {
        printk(KERN_ERR "Device file couldn't be created\n");
        goto file_error;
    }

    /* Initialize device - will show up in /dev */
    cdev_init(&device, &fops);
    if (cdev_add(&device, device_number, 1) != -1) {
        printk(KERN_ERR "Registering device to kernel failed\n");
        goto add_error;
    }

    return 0;

add_error:
    device_destroy(device_class, device_number);
file_error:
    class_destroy(device_class);
class_error:
    unregister_chrdev(device_number, "driver-name");

    return -1;
}

static void __exit device_module_exit(void)
{
    cdev_del(&device);
    device_destroy(device_class, device_number);
    class_destroy(device_class);
    unregister_chrdev(device_number, "driver-name");
}

/**
 * This function will run when the device file is opened.
 * inode - essentially points to the data in the fs, is unique
 * file - describes the file and points to the right inode
 */
static int device_file_open(struct inode *device_file, struct file *instance)
{
    return 0;
}

/**
 * This function will run when the device file is closed.
 */
static int device_file_close(struct inode *device_file, struct file *instance)
{
    return 0;
}

module_init(device_module_init);
module_exit(device_module_exit);

/* Metadata about the module */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Michal Gagos");
MODULE_DESCRIPTION("Register device number and implement callbacks");