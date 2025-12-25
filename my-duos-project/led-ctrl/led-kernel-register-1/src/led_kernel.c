// led_sg2000.c
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/io.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/pinctrl/consumer.h> // 关键：SG2000需要pinctrl
#include <linux/uaccess.h>

// SG2000 GPIO0基地址（根据实际手册调整）
#define SG2000_GPIO0_BASE 0x03020000
#define SG2000_GPIO0_DR (SG2000_GPIO0_BASE + 0x00)
#define SG2000_GPIO0_DDR (SG2000_GPIO0_BASE + 0x04)

// GPIOA29对应的位（需要确认实际引脚映射）
#define GPIOA29_BIT (1 << 29)

// 全局指针
unsigned int *vir_gpio_ddr;
unsigned int *vir_gpio_dr;
struct pinctrl *pinctrl;
struct pinctrl_state *pinctrl_state;

ssize_t led_write(struct file *file, const char __user *user_buf, size_t size,
                  loff_t *loff) {
    char kernel_buf[64] = {0};
    unsigned int old_val;

    printk(KERN_INFO "led_write: size=%zu\n", size);

    if (copy_from_user(kernel_buf, user_buf, size) != 0) {
        printk(KERN_ERR "copy_from_user error\n");
        return -EFAULT;
    }

    old_val = *vir_gpio_dr;
    if (kernel_buf[0] == '1') {
        *vir_gpio_dr = old_val | GPIOA29_BIT;
        printk(KERN_INFO "LED ON: DR 0x%08x -> 0x%08x\n", old_val,
               *vir_gpio_dr);
    } else if (kernel_buf[0] == '0') {
        *vir_gpio_dr = old_val & ~GPIOA29_BIT;
        printk(KERN_INFO "LED OFF: DR 0x%08x -> 0x%08x\n", old_val,
               *vir_gpio_dr);
    } else {
        printk(KERN_WARNING "Invalid command: %c\n", kernel_buf[0]);
        return -EINVAL;
    }

    return 1;
}

int led_open(struct inode *inode, struct file *file) {
    printk(KERN_INFO "led_open\n");
    return 0;
}

int led_release(struct inode *inode, struct file *file) {
    printk(KERN_INFO "led_release\n");
    return 0;
}

static struct file_operations led_fops = {.owner = THIS_MODULE,
                                          .write = led_write,
                                          .open = led_open,
                                          .release = led_release};

static struct miscdevice led_dev = {
    .minor = MISC_DYNAMIC_MINOR, .fops = &led_fops, .name = "led_dev"};

static int __init led_init(void) {
    int ret;
    struct device *dev;

    printk(KERN_INFO "led_init for SG2000\n");

    // 1. 注册misc设备
    ret = misc_register(&led_dev);
    if (ret < 0) {
        printk(KERN_ERR "misc_register failed: %d\n", ret);
        return ret;
    }

    dev = led_dev.this_device;
    printk(KERN_INFO "misc_register succeeded\n");

    // 2. 设置pinctrl（关键！SG2000必须配置）
    pinctrl = devm_pinctrl_get(dev);
    if (IS_ERR(pinctrl)) {
        printk(KERN_WARNING "无法获取pinctrl，尝试继续...\n");
        pinctrl = NULL;
    } else {
        // 选择GPIO状态
        pinctrl_state = pinctrl_lookup_state(pinctrl, "default");
        if (IS_ERR(pinctrl_state)) {
            printk(KERN_WARNING "无法获取default pinctrl状态\n");
        } else {
            ret = pinctrl_select_state(pinctrl, pinctrl_state);
            if (ret < 0) {
                printk(KERN_WARNING "pinctrl_select_state failed: %d\n", ret);
            } else {
                printk(KERN_INFO "pinctrl配置成功\n");
            }
        }
    }

    // 3. 映射GPIO寄存器
    vir_gpio_ddr = ioremap(SG2000_GPIO0_DDR, 4);
    vir_gpio_dr = ioremap(SG2000_GPIO0_DR, 4);

    if (!vir_gpio_ddr || !vir_gpio_dr) {
        printk(KERN_ERR "ioremap failed\n");
        if (pinctrl)
            devm_pinctrl_put(pinctrl);
        misc_deregister(&led_dev);
        return -ENOMEM;
    }

    printk(KERN_INFO "ioremap成功: ddr=%p, dr=%p\n", vir_gpio_ddr, vir_gpio_dr);
    printk(KERN_INFO "初始值: DDR=0x%08x, DR=0x%08x\n", *vir_gpio_ddr,
           *vir_gpio_dr);

    // 4. 配置GPIOA29为输出
    *vir_gpio_ddr |= GPIOA29_BIT;
    printk(KERN_INFO "设置输出方向: DDR=0x%08x\n", *vir_gpio_ddr);

    // 5. 初始化为低电平
    *vir_gpio_dr &= ~GPIOA29_BIT;
    printk(KERN_INFO "初始化低电平: DR=0x%08x\n", *vir_gpio_dr);

    printk(KERN_INFO "SG2000 LED驱动初始化完成，使用GPIOA29\n");
    return 0;
}

static void __exit led_exit(void) {
    printk(KERN_INFO "led_exit\n");

    // 关闭LED
    if (vir_gpio_dr) {
        *vir_gpio_dr &= ~GPIOA29_BIT;
    }

    // 取消映射
    if (vir_gpio_ddr)
        iounmap(vir_gpio_ddr);
    if (vir_gpio_dr)
        iounmap(vir_gpio_dr);

    // 释放pinctrl
    if (pinctrl) {
        devm_pinctrl_put(pinctrl);
    }

    misc_deregister(&led_dev);
    printk(KERN_INFO "LED驱动已卸载\n");
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("LED Driver for SG2000");
module_init(led_init);
module_exit(led_exit);
