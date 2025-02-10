# Char Device

What is a **character device**?

Also called a `char` device it is one type of **device files** available on Linux.

We can create a new char device file manually by running:
``` bash
mknod /dev/<device_name> c <major> <minor>
```

`register_chrdev(...)` is the function which registers a new `char` device.
The arguments it takes in order are:
- Major device number (0 tells the function to select automatically)
- Label that will appear in `proc` devices
- `fops` will define the desired behavior

I feel like the `/proc` filesystem needs a bit more context.

The `/proc` is the directory, where linux keeps its runtime information.
Our inserted module can be viewed in `/proc/modules`.