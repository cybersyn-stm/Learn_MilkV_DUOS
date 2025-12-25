// platform_led.c

#include "linux/fs.h"
#include "linux/gpio.h"
#include "linux/init.h"
#include "linux/miscdevice.h"
#include "linux/module.h"
#include "linux/of.h"
#include "linux/of_gpio.h"
#include "linux/platform_device.h"
#include "linux/uaccess.h"

int gpio_num;

int led_open(struct inode *inode, struct file *file) {
  printk("led_open\n");
  return 0;
}

ssize_t led_write(struct file *file, const char __user *user_buf, size_t size,
                  loff_t *loff) {
  char kernel_buf[64] = {0};
  printk("led_write\n");
  if (copy_from_user(kernel_buf, user_buf, size) != 0) {
    printk("copy_from_user error\n");
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

static struct file_operations led_fops = {
    .owner = THIS_MODULE,
    .open = led_open,
    .write = led_write,
};

struct miscdevice led_miscdevice = {
    .minor = MISC_DYNAMIC_MINOR, .fops = &led_fops, .name = "led_misc"};

int led_probe(struct platform_device *platform_device) {
  printk("led_probe\n");
  printk(
      "compatible is %s\n",
      (char *)of_find_property(platform_device->dev.of_node, "compatible", NULL)
          ->value);
  gpio_num = of_get_named_gpio(platform_device->dev.of_node, "led-gpio", 0);
  if (gpio_num < 0) {
    printk("of_get_named_gpio error\n");
    return -1;
  }

  printk("led gpio is %d\n", gpio_num);
  gpio_request(gpio_num, NULL);
  gpio_direction_output(gpio_num, 0);

  if (misc_register(&led_miscdevice) < 0) {
    printk("misc_register error\n");
    return -1;
  } else {
    printk("misc_register succeed\n");
    return 0;
  }
}

const struct of_device_id of_led_table[] = {
    {
        .compatible = "my_led",
    },
    {},
};

static struct platform_driver led_driver = {
    .probe = led_probe,
    .driver = {.owner = THIS_MODULE,
               .name = "led_driver",
               .of_match_table = of_led_table}};

static int __init led_init(void) {
  printk("led_init\n");
  if (platform_driver_register(&led_driver) < 0) {
    printk("platform_driver_register error\n");
    return -1;
  }
  printk("platform_driver_register succeed\n");
  return 0;
}

static void __exit led_exit(void) {
  printk("led_exit\n");
  gpio_free(gpio_num);
  misc_deregister(&led_miscdevice);
  platform_driver_unregister(&led_driver);
}

MODULE_LICENSE("GPL");
module_init(led_init);
module_exit(led_exit);
