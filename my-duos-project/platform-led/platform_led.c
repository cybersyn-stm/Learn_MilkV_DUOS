#include "asm-generic/gpio.h"
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
  size_t len = min(size, sizeof(kernel_buf) - 1);

  pr_info("led_write, size=%zu\n", size);

  if (copy_from_user(kernel_buf, user_buf, len) != 0) {
    pr_info("copy_from_user error\n");
    return -EFAULT;
  }

  // 典型 echo '0' 的数据是 "0\n"，我们只看第一个字符
  if (kernel_buf[0] == '1') {
    gpio_set_value(gpio_num, 1);
  } else if (kernel_buf[0] == '0') {
    gpio_set_value(gpio_num, 0);
  } else {
    pr_info("invalid value: %c\n", kernel_buf[0]);
    return -EINVAL;
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
  pr_info(
      "compatible is %s\n",
      (char *)of_find_property(platform_device->dev.of_node, "compatible", NULL)
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
