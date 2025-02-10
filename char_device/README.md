# Char Device

### What is a **character device**?

It's a common saying that on linux **everything is a file**, even devices.
Files that operate as an interface to a device are called **device files**.

On linux there are several types of **device files**. A character device (`chrdev`) is one of them.

A character device is non-buffered meaning that it lets us read or write to it character by character instead of using blocks like a block device would.

We can create a new device file manually by running:
``` bash
mknod /dev/<device_name> c <major> <minor>
```
The `c` stands for `char` and is the device file type we are selecting.

To create the device file automatically, we would first need to create a `class` and after that create a `device`. 

---

### Major and Minor numbers

Major device numbers identify a module that can support multiple devices.

Minor device numbers identify the specific device among a group.

Both numbers can either be defined as constant or allocated at runtime dynamically. In a situation where a the desired number is taken, the system will throw an error. Both device numbers are in a range of 0-255.

---

### Code Overview

`register_chrdev(...)` is the function which registers a new `char` device.
The arguments it takes in order are:
- Major device number (0 tells the function to select automatically)
- Label that will appear in `proc` devices
- `fops` will define the desired behavior

I feel like the `/proc` filesystem needs a bit more context.

The `/proc` is the directory, where linux keeps its runtime information.
Our inserted module can be viewed in `/proc/modules`.