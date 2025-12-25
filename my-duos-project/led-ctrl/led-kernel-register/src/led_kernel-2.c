// led_kernel.c
#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/types.h>
#include <linux/uaccess.h>

#define LED_GPIO 509

// 文件操作函数
static ssize_t led_write(struct file *file, const char __user *user_buf,
                         size_t size, loff_t *loff) {
    char buf[2];

    if (size == 0 || size > sizeof(buf))
        return -EINVAL;

    // 复制用户数据
    if (copy_from_user(buf, user_buf, 1))
        return -EFAULT;

    buf[1] = '\0'; // 确保字符串结束

    printk("Received: %s (size=%zu)\n", buf, size);

    // 控制GPIO
    if (buf[0] == '1') {
        gpio_set_value(LED_GPIO, 1);
        printk("LED ON\n");
    } else if (buf[0] == '0') {
        gpio_set_value(LED_GPIO, 0);
        printk("LED OFF\n");
    } else {
        printk("Invalid input: %c (0x%x)\n", buf[0], buf[0]);
        return -EINVAL;
    }

    return 1; // 处理了1个字节
}

static int led_open(struct inode *inode, struct file *file) {
    printk("LED device opened\n");
    return 0;
}

static int led_release(struct inode *inode, struct file *file) {
    printk("LED device released\n");
    return 0;
}

// 文件操作结构体
static struct file_operations led_fops = {
    .owner = THIS_MODULE,
    .open = led_open,
    .write = led_write,
    .release = led_release,
};

// misc设备结构体
static struct miscdevice led_misc = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = "led_kernel",
    .fops = &led_fops,
};

// 模块初始化
static int __init led_init(void) {
    int ret;

    printk("LED Kernel Module Init\n");

    // 申请GPIO
    ret = gpio_request(LED_GPIO, "led_kernel");
    if (ret) {
        printk("Failed to request GPIO %d, error: %d\n", LED_GPIO, ret);
        return ret;
    }

    // 设置为输出，初始低电平
    ret = gpio_direction_output(LED_GPIO, 0);
    if (ret) {
        printk("Failed to set GPIO %d as output, error: %d\n", LED_GPIO, ret);
        gpio_free(LED_GPIO);
        return ret;
    }

    // 注册misc设备
    ret = misc_register(&led_misc);
    if (ret) {
        printk("Failed to register misc device, error: %d\n", ret);
        gpio_free(LED_GPIO);
        return ret;
    }

    printk("LED device registered successfully (GPIO%d)\n", LED_GPIO);
    return 0;
}

// 模块退出
static void __exit led_exit(void) {
    misc_deregister(&led_misc);
    gpio_free(LED_GPIO);
    printk("LED Kernel Module Exit\n");
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Simple LED Driver");
module_init(led_init);
module_exit(led_exit);
