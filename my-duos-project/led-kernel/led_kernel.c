// led_kernel.c
// led_kernel.c

#include "linux/gpio.h"
#include "linux/init.h"
#include "linux/module.h"

int gpio_num = 509;

static int __init led_init(void) {
    printk("led_init\n");
    gpio_request(gpio_num, NULL);
    gpio_direction_output(gpio_num, 0);
    gpio_set_value(gpio_num, 1);
    return 0;
}

static void __exit led_exit(void) {
    printk("led_exit\n");
    gpio_request(gpio_num, NULL);
    gpio_direction_output(gpio_num, 0);
    gpio_set_value(gpio_num, 0);
    gpio_free(gpio_num);
}

MODULE_LICENSE("GPL");
module_init(led_init);
module_exit(led_exit);
