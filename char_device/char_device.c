#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

static ssize_t driver_file_read(struct file *, char *, size_t, loff_t *);

static struct file_operations driver_fops =
{
    .owner      = THIS_MODULE,
    .read       = driver_file_read,
};

static int driver_major = 0;

static const char driver_name[] = "char_device";
static const char driver_hello_string[] = "Hello world from kernel module\n";
static const ssize_t driver_hello_count = sizeof(driver_hello_string);

static int __init driver_init(void)
{
    // Register character device
    int result = 0;
    result = register_chrdev(driver_major, driver_name, &driver_fops);

    if (result < 0) {
        pr_err("%s: Can't register character device with error code = %i\n", driver_name, result);
        return result;
    }

    driver_major = result;
    pr_info("%s: Registered chrdev with major number = %i and minor numbers 0-255", driver_name, driver_major);

    return 0;
}

static void __exit driver_exit(void)
{
    pr_info("%s: Driver is exiting\n", driver_name);

    if(driver_major != 0) {
        unregister_chrdev(driver_major, driver_name);
    }

    return;
}

static ssize_t driver_file_read(struct file *file_ptr, char *user_buffer, size_t length, loff_t *position)
{
    pr_info("%s: Device file read at offset = %i, read bytes count = %u\n", driver_name, (int)*position, (unsigned int)length);

    if(*position >= driver_hello_count) {
        return 0;
    }

    if(*position + length > driver_hello_count) {
        length = driver_hello_count - *position;
    }

    if(copy_to_user(user_buffer, driver_hello_string + *position, length) != 0) {
        return -EFAULT;
    }

    *position += length;
    return length;
}

/**
 * Metadata
 */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Michal Gagos");
MODULE_DESCRIPTION("A driver that registers a character device");

module_init(driver_init);
module_exit(driver_exit);