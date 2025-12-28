#include "linux/export.h"
#include "linux/printk.h"
#include <linux/err.h>
#include <linux/fs.h>
#include <linux/gpio/consumer.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/platform_device.h>
#include <linux/uaccess.h>

#define High_Voltage 1
#define Low_Voltage 0
static struct gpio_desc *gpioa29_desc;
static int gpioa29_num = -1;

/*======================字符设备接口============================*/

/*打开gpio文件*/
static int gpioa29_open(struct inode *inode, struct file *file) {
  pr_info("GPIOA29:device opened\n");
  return 0;
}

/*gpio操作*/
static ssize_t gpioa29_write(struct file *file, const char __user *user_buf,
                             size_t size, loff_t *ppos) {
  char c;
  // 用户态输入不能小于0
  if (size < 1)
    return -EINVAL;
  // copy_from_user 成功返回0，失败返回未读取的字符数量
  if (copy_from_user(&c, user_buf, 1))
    return -EINVAL;
  if (c == '1') {
    gpiod_set_value(gpioa29_desc, High_Voltage);
    pr_info("GPIOA29 set: %d\n", High_Voltage);
  } else if (c == '0') {
    gpiod_set_value(gpioa29_desc, Low_Voltage);
    pr_info("GPIOA29 set: %d\n", Low_Voltage);
  } else {
    pr_info("GPIOA29: invalid write '%c'\n", c);
    return -EINVAL;
  }

  return 1;
}

/*文件操作注册*/
static const struct file_operations gpioa29_fops = {
    .owner = THIS_MODULE,
    .open = gpioa29_open,
    .write = gpioa29_write,
};

static const struct miscdevice gpioa29_miscdev = {
    .minor = MISC_DYNAMIC_MINOR,
    .fops = &gpioa29_fops,
    .name = "gpioa29",
};

/*==============probe=============*/
static int gpioa29_probe(struct platform_device *pdev) {
  struct device *dev = &pdev->dev;
  struct device_node *np = dev->of_node;
  const char *compat;
  int ret;

  pr_info("GPIOA29: probe for device '%s'\n", dev_name(dev));

  if (!np) {
    dev_err(dev, "GPIOA29: dev->of_node is NULL, expect DT-created device. "
                 "Check DTS & of_match_table.\n");
    return -ENODEV;
  }
}
