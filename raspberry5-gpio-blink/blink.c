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

#include <linux/init.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Michal Gagos");

static int __init gpio_module_init(void)
{

}

static void __exit gpio_module_exit(void)
{

}

module_init(gpio_module_init);
module_exit(gpio_module_exit);