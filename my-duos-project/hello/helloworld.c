// helloworld.c
#include "errno.h"
#include "linux/i2c-dev.h"
#include "linux/init.h"
#include "linux/module.h"
#include "linux/printk.h"
static int __init helloworld_init(void) {
    printk("helloworld\n");
    return 0;
}

static void __exit helloworld_exit(void) { printk("goodbye\n"); }

MODULE_LICENSE("GPL");
module_init(helloworld_init);
module_exit(helloworld_exit);
