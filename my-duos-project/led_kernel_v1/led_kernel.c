// led_kernel_gpio.c
// 使用GPIO子系统API的LED驱动

#include <linux/errno.h>
#include <linux/fs.h>
#include <linux/gpio.h> // GPIO子系统API
#include <linux/init.h>
#include <linux/io.h> // 如果还需要寄存器操作
#include <linux/kernel.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/string.h>
#include <linux/types.h>
#include <linux/uaccess.h>

// 定义GPIO编号
// 注意：这里的509是Linux GPIO编号，不是硬件引脚号
// 从之前的debug信息看，GPIO 509对应硬件上的某个GPIO
#define LED_GPIO 509

// 如果还需要直接寄存器操作（可选，但推荐只用GPIO API）
#define GPIO509_DDR (0x03020000 + 0x000)
#define GPIO509_DR (0x03020000 + 0x004)
#define GPIO509_REG 29

// 设备结构体，用于保存状态
struct led_device {
  struct miscdevice miscdev;
  int gpio_initialized;
  int led_state; // 0=off, 1=on
};

static struct led_device led_dev_data;

// Write device function
static ssize_t led_write(struct file *file, const char __user *user_buf,
                         size_t size, loff_t *loff) {
  char kernel_buf[64] = {0};
  size_t len;

  printk(KERN_DEBUG "led_write: called, size=%zu\n", size);

  // 确保有数据
  if (size == 0) {
    printk(KERN_WARNING "led_write: no data\n");
    return 0;
  }

  // 限制缓冲区大小
  len = (size < sizeof(kernel_buf)) ? size : sizeof(kernel_buf) - 1;

  // 从用户空间复制数据
  if (copy_from_user(kernel_buf, user_buf, len)) {
    printk(KERN_ERR "led_write: copy_from_user failed\n");
    return -EFAULT;
  }

  // 确保字符串以NULL结尾
  kernel_buf[len] = '\0';

  printk(KERN_INFO "led_write: received '%s' (len=%zu)\n", kernel_buf, len);

  // 处理命令
  if (kernel_buf[0] == '1') {
    // 点亮LED
    gpio_set_value(LED_GPIO, 1);
    led_dev_data.led_state = 1;
    printk(KERN_INFO "led_write: LED ON\n");
  } else if (kernel_buf[0] == '0') {
    // 熄灭LED
    gpio_set_value(LED_GPIO, 0);
    led_dev_data.led_state = 0;
    printk(KERN_INFO "led_write: LED OFF\n");
  } else if (strncmp(kernel_buf, "status", 6) == 0) {
    // 查询状态
    printk(KERN_INFO "led_write: LED status: %s\n",
           led_dev_data.led_state ? "ON" : "OFF");
    // 注意：这里只是打印，如果需要返回状态给用户，需要实现read函数
  } else if (strncmp(kernel_buf, "toggle", 6) == 0) {
    // 切换状态
    led_dev_data.led_state = !led_dev_data.led_state;
    gpio_set_value(LED_GPIO, led_dev_data.led_state);
    printk(KERN_INFO "led_write: LED toggled to %s\n",
           led_dev_data.led_state ? "ON" : "OFF");
  } else {
    printk(KERN_WARNING "led_write: invalid command '%c'\n", kernel_buf[0]);
    return -EINVAL;
  }

  return len; // 返回处理的字节数
}

// Read device function (可选，用于读取状态)
static ssize_t led_read(struct file *file, char __user *user_buf, size_t size,
                        loff_t *loff) {
  char buf[32];
  int len;

  // 如果已经读取过，返回0表示结束
  if (*loff > 0) {
    return 0;
  }

  // 格式化状态字符串
  len = snprintf(buf, sizeof(buf), "LED state: %d\n", led_dev_data.led_state);

  // 复制到用户空间
  if (copy_to_user(user_buf, buf, len)) {
    return -EFAULT;
  }

  *loff = len; // 更新偏移量
  return len;
}

// Open device function
static int led_open(struct inode *inode, struct file *file) {
  printk(KERN_INFO "led_open: device opened\n");
  return 0;
}

// Release device function
static int led_release(struct inode *inode, struct file *file) {
  printk(KERN_INFO "led_release: device closed\n");
  return 0;
}

// File operations structure
static const struct file_operations led_fops = {
    .owner = THIS_MODULE,
    .open = led_open,
    .read = led_read, // 添加读取功能
    .write = led_write,
    .release = led_release,
};

// Module init function
static int __init led_init(void) {
  int ret;

  printk(KERN_INFO "======================================\n");
  printk(KERN_INFO "LED GPIO Driver Initialization\n");
  printk(KERN_INFO "Using GPIO %d\n", LED_GPIO);
  printk(KERN_INFO "======================================\n");

  // 初始化设备结构体
  memset(&led_dev_data, 0, sizeof(led_dev_data));
  led_dev_data.led_state = 0; // 初始状态为关

  // 1. 申请GPIO
  ret = gpio_request(LED_GPIO, "led_kernel");
  if (ret) {
    printk(KERN_ERR "gpio_request failed for GPIO %d: %d\n", LED_GPIO, ret);

    // 可能GPIO已经被占用，尝试检查并处理
    if (ret == -EBUSY) {
      printk(KERN_WARNING "GPIO %d is busy, trying to free it...\n", LED_GPIO);

      // 尝试强制释放（可能不安全，但可以尝试）
      gpio_free(LED_GPIO);

      // 再次尝试申请
      ret = gpio_request(LED_GPIO, "led_kernel");
      if (ret) {
        printk(KERN_ERR "Still failed to request GPIO %d: %d\n", LED_GPIO, ret);
        return ret;
      }

      printk(KERN_INFO "Successfully re-requested GPIO %d\n", LED_GPIO);
    } else {
      return ret;
    }
  }

  printk(KERN_INFO "GPIO %d requested successfully\n", LED_GPIO);
  led_dev_data.gpio_initialized = 1;

  // 2. 配置GPIO为输出模式，初始化为低电平（LED灭）
  ret = gpio_direction_output(LED_GPIO, 0);
  if (ret) {
    printk(KERN_ERR "gpio_direction_output failed: %d\n", ret);
    gpio_free(LED_GPIO);
    return ret;
  }

  printk(KERN_INFO "GPIO %d configured as output, initial state: LOW\n",
         LED_GPIO);

  // 3. 设置初始值（确保LED灭）
  gpio_set_value(LED_GPIO, 0);

  // 4. 配置miscdevice
  led_dev_data.miscdev.minor = MISC_DYNAMIC_MINOR;
  led_dev_data.miscdev.name = "led_kernel";
  led_dev_data.miscdev.fops = &led_fops;
  led_dev_data.miscdev.mode = 0666; // 设置默认权限

  // 5. 注册miscdevice
  ret = misc_register(&led_dev_data.miscdev);
  if (ret) {
    printk(KERN_ERR "misc_register failed: %d\n", ret);
    gpio_free(LED_GPIO);
    return ret;
  }

  printk(KERN_INFO "Device registered: /dev/%s\n", led_dev_data.miscdev.name);

  // 6. 输出成功信息
  printk(KERN_INFO "======================================\n");
  printk(KERN_INFO "LED Driver Loaded Successfully!\n");
  printk(KERN_INFO "  Device: /dev/led_kernel\n");
  printk(KERN_INFO "  GPIO:   %d\n", LED_GPIO);
  printk(KERN_INFO "  State:  OFF\n");
  printk(KERN_INFO "======================================\n");

  return 0;
}

// Module exit function
static void __exit led_exit(void) {
  printk(KERN_INFO "======================================\n");
  printk(KERN_INFO "LED GPIO Driver Unloading\n");
  printk(KERN_INFO "======================================\n");

  // 1. 确保LED熄灭
  if (led_dev_data.gpio_initialized) {
    gpio_set_value(LED_GPIO, 0);
    printk(KERN_INFO "LED turned OFF\n");
  }

  // 2. 注销设备
  misc_deregister(&led_dev_data.miscdev);
  printk(KERN_INFO "Device unregistered\n");

  // 3. 释放GPIO
  if (led_dev_data.gpio_initialized) {
    gpio_free(LED_GPIO);
    printk(KERN_INFO "GPIO %d freed\n", LED_GPIO);
  }

  printk(KERN_INFO "======================================\n");
  printk(KERN_INFO "LED Driver Unloaded\n");
  printk(KERN_INFO "======================================\n");
}

// Module information
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("GPIO LED Driver using GPIO Subsystem API");
MODULE_VERSION("1.1");

module_init(led_init);
module_exit(led_exit);
