# Char Device

`register_chrdev(...)` is the function which registers a new `char` device.
The arguments it takes in order are:
- Major device number (0 tells the function to select automatically)
- Label that will appear in proc devices
- `fops` will define the desired behavior