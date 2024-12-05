/**
 * The legacy way of accessing GPIO on a raspberry pi
 * is to access them using numbers.
 * 
 * Raspberry 5 uses the new kernel GPIOD module.
 * This means that we need to use the device tree,
 * in order to access a gpio_desc.
 * 
 * The Raspberry 5 uses the Broadcom BCM2712 as its gpio chip.
 * 
 * We can access its device tree source at:
 * arch/arm64/boot/dts/broadcom/bcm2712-rpi-5-b.dts
 * 
 * We can override that file using something called a device tree overlay.
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/gpio/consumer.h>

/**
 * We need access to a struct device in order to get a struct gpio_desc,
 * because of this we will use a platform driver
 */
static int dt_probe(struct platform_device* pdev);
static void dt_remove(struct platform_device* pdev);

static const struct of_device_id device_dt_ids[] = {
    { .compativle = "mgagos,blink" },
    { }
};
MODULE_DEVICE_TABLE(of, device_dt_ids);

static struct platform_driver pd {
    .probe = dt_probe,
    .remove = dt_remove,
    .driver = {
        .name = "blink",
        .of_match_table = of_match_ptr(device_dt_ids),
    },
};

static int dt_probe(struct platform_device* pdev)
{
    struct device* dev = &pdev->dev;
    struct gpio_desc* led = gpiod_get(dev, "led", GPIOD_OUT_HIGH);

    printk(KERN_INFO "Current led gpio state is: %d\n", gpiod_get_value(led));
}

static void dt_remove(struct platform_device* pdev)
{
    printk(KERN_INFO "Device: Remove was called\n");
}

module_platform_driver(pd);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Michal Gagos");