# Hello World
This module is meant to be the starting point for anyone wanting to learn kernel development.

## Compiling and Inserting the module

To compile the module just run `make`. The makefile essentially just runs another makefile that is provided, by the linux kernel developers.

To insert the module at runtime we can run `insmod <module_name.ko>`. After that it will show up in `lsmod` command output. When we want to remove it we run `rmmod <module_name>`.

To see any kernel log output we need to run `dmesg`.


## Explanation

We need to let the kernel know what functions to run on startup as well as on exit. We do that using the following functions:
``` c
/**
 * We declare our custom startup and exit functions
 */
static int __init run_on_insert(void) {
    // Do something on startup
}

static void __exit run_on_remove(void) {
    // Do something on exit
}

/**
 * These are a part of #include<linux/module.h>
 */
module_init(run_on_insert);
module_exit(run_on_remove);
```

The functions are declared as `static`, because they explicitly can't be visible for another file. They can't take any arguments, so they are annotated as `(void)`.

The annotations `__init` and `__exit` are part of `#include<linux/init.h>`. They might seem trivial at first, but they let the kernel know that it can optimize these functions, by placing them in a different section. It knows that the `__init` function will run only once, so the memory containing it can be freed once it ran.

If we want to print something to the kernel log, we use `printk()`. It won't be visible from user space so we need to run the `dmesg` command to see the kernel logs.

The last part of the driver is the metadata that provides anyone reading our code with information about what it does, who wrote it and what is its license.