#include "linux/export.h"
#include "linux/kern_levels.h"
#include <linux/delay.h>
#include <linux/errno.h>
#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/types.h>
#include <linux/uaccess.h>

#define LED_GPIO 509
#define HIGH_VOLTE 1
#define LOW_VOLTE 0
// 文件操作函数
static ssize_t led_write(struct file *file, const char __user *user_buf,
                         size_t size, loff_t *loff) {
    char buf[64];
    char ch_user[64];
    ssize_t ret = 0;
    int i;
    int j;
    // 允许输入空数据
    if (size == 0)
        return 0;
    // 判断用户buf内容是否大于size
    if (size > sizeof(buf)) {
        printk(KERN_WARNING "Write size %zu exceeds buffer size %zu\n", size,
               sizeof(buf));
        size = sizeof(buf); // 只处理缓冲区内容
    }

    // 复制用户数据 copy_from_user成功返回0，失败返回未能复制字节数
    if (copy_from_user(buf, user_buf, size)) {
        printk(KERN_ERR "Faild to copy data from user space\n");
        return -EFAULT;
    }
    // 如果用户buf内容符合要求 确保字符串有终止符
    if (size < sizeof(buf)) {
        buf[size] = '\0';
    } else {
        buf[size - 1] = '\n';
    }
    // 处理缓冲区内容
    for (i = 0, j = 0; i < size && j < sizeof(ch_user); i++) {
        char ch = buf[i];
        if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r') {
            continue; // 跳过无效字符
        } else {
            ch_user[j++] = ch;
            ret++;
        }
    }
    ch_user[j] = '\0'; // 添加字符串终止符
    printk(KERN_INFO "User input: %s\n", ch_user);
    // GPIO控制LED
    if (strcmp(ch_user, "1") == 0) {
        gpio_set_value(LED_GPIO, HIGH_VOLTE);
        printk(KERN_INFO "LED ON\n");
    } else if (strcmp(ch_user, "0") == 0) {
        gpio_set_value(LED_GPIO, LOW_VOLTE);
        printk(KERN_INFO "LED OFF\n");
    } else if (strcmp(ch_user, "LED_FLASH") == 0) {
        for (i = 0; i < 5; i++) {
            gpio_set_value(LED_GPIO, HIGH_VOLTE);
            msleep(500);
            gpio_set_value(LED_GPIO, LOW_VOLTE);
            msleep(500);
            printk(KERN_INFO "LED FLASH\n");
        }
    } else {
        printk(KERN_ERR "Invalid command: %s\n", ch_user);
        return -EINVAL;
    }

    if (ret == 0 && size > 0) {
        printk(KERN_ERR "No valid data found in user input\n");
        return -EINVAL;
    }

    return size;
}

static int led_open(struct inode *inode, struct file *file) {
    printk("LED device opened\n");
    return 0;
}

static int led_release(struct inode *inode, struct file *file) {
    printk("LED device closed\n");
    return 0;
}

static struct file_operations led_fops = {
    .owner = THIS_MODULE,
    .open = led_open,
    .write = led_write,
    .release = led_release,
};

static struct miscdevice led_misc = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = "led_kernel",
    .fops = &led_fops,
};

static int __init led_init(void) {
    int ret;

    printk("LED Kernel Module INit\n");

    ret = gpio_request(LED_GPIO, "led_kernel");
    if (ret) {
        printk("Failed to request GPIO %d,error: %d\n", LED_GPIO, ret);
        return ret;
    }

    ret = gpio_direction_output(LED_GPIO, LOW_VOLTE);
    if (ret) {
        printk("Failed to set GPIO %d as output,error: %d\n", LED_GPIO, ret);
        gpio_free(LED_GPIO);
        return ret;
    }

    ret = misc_register(&led_misc);
    if (ret) {
        printk("Failed to register misc device,error: %d\n", ret);
        gpio_free(LED_GPIO);
        return ret;
    }

    printk("LED Kernel Module Initialized Successfully\n");
    printk("Enter command\n '1' = turn on LED \n '0' = turn off LED \n "
           "'LED_FLASH' = flash LED\n");
    return 0;
}
static void __exit led_exit(void) {
    misc_deregister(&led_misc);
    gpio_set_value(LED_GPIO, LOW_VOLTE);
    gpio_free(LED_GPIO);
    printk("LED Kernel Module Exit\n");
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A simple LED kernel module using GPIO and misc device");

module_init(led_init);
module_exit(led_exit);
