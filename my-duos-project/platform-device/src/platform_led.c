// platform_led_final.c
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/of_gpio.h>
#include <linux/platform_device.h>
#include <linux/uaccess.h>

static int gpio_num = -1;
static bool gpio_active_low = false;

int led_open(struct inode *inode, struct file *file) {
  printk("led_open\n");
  return 0;
}

ssize_t led_write(struct file *file, const char __user *user_buf, size_t size,
                  loff_t *loff) {
  char kernel_buf[64] = {0};
  int physical_level;

  printk("led_write\n");

  if (copy_from_user(kernel_buf, user_buf, size) != 0) {
    printk("copy_from_user error\n");
    return -EFAULT;
  }

  if (gpio_num < 0) {
    printk("GPIO not initialized\n");
    return -ENODEV;
  }

  // 处理 GPIO_ACTIVE_LOW
  if (kernel_buf[0] == '1') {
    // 用户要打开LED
    physical_level = gpio_active_low ? 0 : 1;
  } else if (kernel_buf[0] == '0') {
    // 用户要关闭LED
    physical_level = gpio_active_low ? 1 : 0;
  } else {
    printk("Invalid input: %c\n", kernel_buf[0]);
    return -EINVAL;
  }

  gpio_set_value(gpio_num, physical_level);
  return size;
}

static struct file_operations led_fops = {
    .owner = THIS_MODULE,
    .open = led_open,
    .write = led_write,
};

struct miscdevice led_miscdevice = {
    .minor = MISC_DYNAMIC_MINOR, .fops = &led_fops, .name = "led_misc"};

int led_probe(struct platform_device *pdev) {
  struct device *dev = &pdev->dev;
  struct device_node *np = dev->of_node;
  enum of_gpio_flags flags;
  int ret;

  printk("led_probe: Device %s\n", dev_name(dev));

  // 检查设备树节点
  if (!np) {
    dev_err(dev, "No device tree node\n");
    return -ENODEV;
  }

  printk("Device tree node name: %s\n", np->name);

  // 获取GPIO，包括标志位
  gpio_num = of_get_named_gpio_flags(np, "led_gpio", 0, &flags);
  if (gpio_num < 0) {
    dev_err(dev, "Failed to get 'led-gpio' property: %d\n", gpio_num);
    return gpio_num;
  }

  // 检查GPIO极性
  gpio_active_low = (flags & OF_GPIO_ACTIVE_LOW) ? true : false;

  printk("GPIO number: %d, Active %s\n", gpio_num,
         gpio_active_low ? "LOW" : "HIGH");

  // 申请GPIO
  ret = gpio_request(gpio_num, "led_misc");
  if (ret) {
    dev_err(dev, "Failed to request GPIO %d: %d\n", gpio_num, ret);
    return ret;
  }

  // 配置GPIO为输出
  // 初始状态：关闭（如果是ACTIVE_LOW，初始设为1；否则设为0）
  ret = gpio_direction_output(gpio_num, gpio_active_low ? 1 : 0);
  if (ret) {
    dev_err(dev, "Failed to set GPIO direction: %d\n", ret);
    gpio_free(gpio_num);
    return ret;
  }

  // 注册杂项设备
  ret = misc_register(&led_miscdevice);
  if (ret) {
    dev_err(dev, "Failed to register misc device: %d\n", ret);
    gpio_free(gpio_num);
    return ret;
  }

  printk("led_probe succeed. Device node: /dev/led_misc\n");
  return 0;
}

int led_remove(struct platform_device *pdev) {
  printk("led_remove\n");
  misc_deregister(&led_miscdevice);

  if (gpio_num >= 0) {
    gpio_free(gpio_num);
  }

  return 0;
}

const struct of_device_id of_led_table[] = {
    {.compatible = "my_led"},
    {},
};
MODULE_DEVICE_TABLE(of, of_led_table);

static struct platform_driver led_driver = {
    .probe = led_probe,
    .remove = led_remove,
    .driver =
        {
            .owner = THIS_MODULE,
            .name = "led_driver",
            .of_match_table = of_led_table,
        },
};

static int __init led_init(void) {
  int ret;

  printk("led_init\n");

  ret = platform_driver_register(&led_driver);
  if (ret) {
    printk("platform_driver_register error: %d\n", ret);
    return ret;
  }

  printk("platform_driver_register succeed\n");
  return 0;
}

static void __exit led_exit(void) {
  printk("led_exit\n");
  platform_driver_unregister(&led_driver);
}

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("LED Driver for Milk-V DuoS");
module_init(led_init);
module_exit(led_exit);
