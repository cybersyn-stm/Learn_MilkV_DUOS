#include "asm-generic/gpio.h"
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
  pr_info("led_write\n");
  if (copy_from_user(kernel_buf, user_buf, size) != 0) {
    pr_info("copy_from_user error\n");
    return -1;
  } else {
    if (kernel_buf[0] == '1') {
      gpio_set_value(gpio_num, 1);
    } else if (kernel_buf[0] == '0') {
      gpio_set_value(gpio_num, 0);
    }
    return 0;
  }
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
  gpio_request(gpio_num, NULL);
  gpio_direction_output(gpio_num, 0);

  if (misc_register(&led_miscdevice) < 0) {
    pr_info("misc_register error\n");
    return -1;
  } else {
    pr_info("misc_register succed\n");
    return 0;
  }
}
