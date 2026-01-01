#include "asm-generic/gpio.h"
#include "linux/delay.h"
#include "linux/device.h"
#include "linux/export.h"
#include "linux/fs.h"
#include "linux/gpio.h"
#include "linux/init.h"
#include "linux/miscdevice.h"
#include "linux/module.h"
#include "linux/of.h"
#include "linux/of_gpio.h"
#include "linux/platform_device.h"
#include "linux/printk.h"
#include "linux/uaccess.h"
int gpio_num;

int led_open(struct inode *inode, struct file *file) {
    printk("led_open\n");
    return 0;
}

ssize_t led_write(struct file *file, const char __user *user_buf, size_t size,
                  loff_t *loff) {
    char kernel_buf[64] = {0};
    char buff_handle[64];
    int i;
    size_t len = min(size, sizeof(kernel_buf) - 1);

    pr_info("led_write, size=%zu\n", size);

    if (copy_from_user(kernel_buf, user_buf, len) != 0) {
        pr_info("copy_from_user error\n");
        return -EFAULT;
    } else {
        pr_info("copy_from_user succed, kernel_buf=%s\n", kernel_buf);
        for (i = 0; i < len && kernel_buf[i] != '\0'; i++) {
            if (kernel_buf[i] != '\n' && kernel_buf[i] != '\r') {
                buff_handle[i] = kernel_buf[i];
            } else {
                buff_handle[i] = '\0';
                break;
            }
        }
    }
    if (strcmp(buff_handle, "on") == 0) {
        gpio_set_value(gpio_num, 1);
        pr_info("LED is ON\n");
    } else if (strcmp(buff_handle, "off") == 0) {
        gpio_set_value(gpio_num, 0);
        pr_info("LED is OFF\n");
    } else if (strcmp(buff_handle, "flash") == 0) {
        pr_info("LED is flash\n");
        for (i = 0; i < 5; i++) {
            gpio_set_value(gpio_num, 1);
            msleep(200);
            gpio_set_value(gpio_num, 0);
            msleep(200);
        }
    } else {
        pr_info("Invalid command. Use 'on' or 'off'.\n");
    }

    return size; // 非常重要：告诉用户态“我处理了 size 字节”
}
// register file_operations
static struct file_operations led_fops = {
    .owner = THIS_MODULE,
    .open = led_open,
    .write = led_write,
};

// register miscdevice
struct miscdevice led_miscdevice = {
    .minor = MISC_DYNAMIC_MINOR,
    .fops = &led_fops,
    .name = "led_misc",
};

int led_probe(struct platform_device *platform_device) {
    pr_info("led_probe\n");
    pr_info("compatible is %s\n",
            (char *)of_find_property(platform_device->dev.of_node, "compatible",
                                     NULL)
                ->value);
    gpio_num = of_get_named_gpio(platform_device->dev.of_node, "led_gpio", 0);
    if (gpio_num < 0) {
        pr_info("of_get_named_gpio error\n");
        return -1;
    }

    pr_info("led gpio is %d\n", gpio_num);
    gpio_request(gpio_num, "my_led");
    gpio_direction_output(gpio_num, 0);

    if (misc_register(&led_miscdevice) < 0) {
        pr_info("misc_register error\n");
        return -1;
    } else {
        pr_info("misc_register succed\n");
        return 0;
    }
}

const struct of_device_id of_led_table[] = {
    {
        .compatible = "my_led",
    },
};

static struct platform_driver led_driver = {
    .probe = led_probe,
    .driver = {.owner = THIS_MODULE,
               .name = "led_driver",
               .of_match_table = of_led_table}};

static int __init led_init(void) {
    pr_info("led_init\n");
    if (platform_driver_register(&led_driver) < 0) {
        pr_info("platform_driver_register error\n");
        return -1;
    }
    pr_info("platform_driver_register succed\n");
    return 0;
}

static void __exit led_exit(void) {
    pr_info("led_exit\n");
    gpio_free(gpio_num);
    misc_deregister(&led_miscdevice);
    platform_driver_unregister(&led_driver);
}

MODULE_LICENSE("GPL");
module_init(led_init);
module_exit(led_exit);
