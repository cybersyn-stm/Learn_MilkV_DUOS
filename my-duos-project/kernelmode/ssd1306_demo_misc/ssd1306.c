#include "linux/string.h"
#include "linux/types.h"
#include <linux/device.h>
#include <linux/i2c.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/mutex.h>
#include <linux/slab.h>
#include <linux/sysfs.h>
#include <linux/uaccess.h>

#define SSD1306_NAME "ssd1306"
#define SSD1306_I2C_ADDRESS 0x3C // 请结合你硬件实际地址选择
#define SSD1306_I2C_CMD 0x00     // 控制字节: 命令
#define SSD1306_I2C_DATA 0x40    // 控制字节: 数据
#define SSD1306_WIDTH 128
#define SSD1306_HEIGHT 64

struct ssd1306_data {
    struct i2c_client *client;
    struct mutex lock;
    struct miscdevice miscdev;
};

/* 发送命令/数据的底层函数 */
static int ssd1306_write_byte(struct i2c_client *client, uint8_t control,
                              uint8_t data) {
    uint8_t buf[2];
    struct i2c_msg msg;
    int ret;

    buf[0] = control; // 控制字节, 0x00=命令, 0x40=数据
    buf[1] = data;

    msg.addr = client->addr;
    msg.flags = 0;
    msg.len = 2;
    msg.buf = buf;

    ret = i2c_transfer(client->adapter, &msg, 1);
    if (ret < 1) {
        dev_err(&client->dev, "i2c_transfer failed: %d\n", ret);
        return -EIO;
    }
    return 0;
}

/* 一次性发送 data payload（前面自动加 0x40 控制字节） */
static int ssd1306_write_data_buf(struct i2c_client *client, const u8 *data,
                                  size_t len) {
    struct i2c_msg msg;
    u8 *buf;
    int ret;

    if (!len)
        return 0;

    buf = kmalloc(len + 1, GFP_KERNEL);
    if (!buf)
        return -ENOMEM;

    buf[0] = SSD1306_I2C_DATA; // 控制字节: 数据
    memcpy(&buf[1], data, len);

    msg.addr = client->addr;
    msg.flags = 0;
    msg.len = len + 1;
    msg.buf = buf;

    ret = i2c_transfer(client->adapter, &msg, 1);
    kfree(buf);

    if (ret < 1) {
        dev_err(&client->dev, "i2c_transfer failed: %d\n", ret);
        return -EIO;
    }

    return 0;
}

static int ssd1306_write_command(struct i2c_client *client, uint8_t data) {
    return ssd1306_write_byte(client, SSD1306_I2C_CMD, data);
}

static int ssd1306_write_data(struct i2c_client *client, uint8_t data) {
    return ssd1306_write_byte(client, SSD1306_I2C_DATA, data);
}

/* SSD1306 初始化命令序列 */
static int ssd1306_init_display(struct i2c_client *client) {
    int ret = 0;

    ret |= ssd1306_write_command(client, 0xAE); // Display OFF
    ret |= ssd1306_write_command(client, 0x20); // Set Memory Addressing Mode
    ret |= ssd1306_write_command(client, 0x00); // Horizontal Addressing Mode
    ret |= ssd1306_write_command(
        client, 0xB0); // Set Page Start Address for Page Addressing Mode, 0-7
    ret |= ssd1306_write_command(client, 0xC8); // COM Output Scan Direction
    ret |= ssd1306_write_command(client, 0x00); // Set low column address
    ret |= ssd1306_write_command(client, 0x10); // Set high column address
    ret |= ssd1306_write_command(client, 0x40); // Set start line address
    ret |= ssd1306_write_command(client, 0x81); // Set contrast control
    ret |= ssd1306_write_command(client, 0xFF); //
    ret |= ssd1306_write_command(client, 0xA1); // Set segment re-map 0 to 127
    ret |= ssd1306_write_command(client, 0xA6); // Normal display
    ret |= ssd1306_write_command(client, 0xA8); // Set multiplex ratio(1 to 64)
    ret |= ssd1306_write_command(client, 0x3F); //
    ret |= ssd1306_write_command(client, 0xA4); // Output RAM to display
    ret |= ssd1306_write_command(client, 0xD3); // Set display offset
    ret |= ssd1306_write_command(client, 0x00); // No offset
    ret |= ssd1306_write_command(
        client, 0xD5); // Set display clock divide ratio/oscillator frequency
    ret |= ssd1306_write_command(client, 0xF0); // Set divide ratio
    ret |= ssd1306_write_command(client, 0xD9); // Set pre-charge period
    ret |= ssd1306_write_command(client, 0x22); //
    ret |= ssd1306_write_command(client,
                                 0xDA); // Set COM pins hardware configuration
    ret |= ssd1306_write_command(client, 0x12);
    ret |= ssd1306_write_command(client, 0xDB); // Set vcomh
    ret |= ssd1306_write_command(client, 0x20); // 0.77xVcc
    ret |= ssd1306_write_command(client, 0x8D); // Set DC-DC enable
    ret |= ssd1306_write_command(client, 0x14); //
    ret |= ssd1306_write_command(client, 0xAF); // Display ON (修正：0xAF)

    if (ret != 0) {
        dev_err(&client->dev, "SSD1306 initialization sequence failed\n");
        return -EIO;
    }
    return 0;
}

/* Sysfs */
static ssize_t ssd1306_command_store(struct device *dev,
                                     struct device_attribute *attr,
                                     const char *buf, size_t count) {
    struct i2c_client *client = to_i2c_client(dev);
    struct ssd1306_data *data = i2c_get_clientdata(client);
    uint8_t command;
    int ret;

    if (sscanf(buf, "%hhx", &command) != 1) {
        dev_err(dev, "Invalid command format\n");
        return -EINVAL;
    }

    mutex_lock(&data->lock);
    ret = ssd1306_write_command(client, command);
    mutex_unlock(&data->lock);

    return ret ? ret : count;
}

static ssize_t ssd1306_data_store(struct device *dev,
                                  struct device_attribute *attr,
                                  const char *buf, size_t count) {
    struct i2c_client *client = to_i2c_client(dev);
    struct ssd1306_data *data = i2c_get_clientdata(client);
    uint8_t v;
    int ret;

    if (sscanf(buf, "%hhx", &v) != 1) {
        dev_err(dev, "Invalid data format\n");
        return -EINVAL;
    }

    mutex_lock(&data->lock);
    ret = ssd1306_write_data(client, v);
    mutex_unlock(&data->lock);

    return ret ? ret : count;
}

/* 仍保持你的用法：cat 触发 init（不建议，但可用） */
static ssize_t ssd1306_init_show(struct device *dev,
                                 struct device_attribute *attr, char *buf) {
    struct i2c_client *client = to_i2c_client(dev);
    struct ssd1306_data *data = i2c_get_clientdata(client);
    int ret;

    mutex_lock(&data->lock);
    ret = ssd1306_init_display(client);
    mutex_unlock(&data->lock);

    if (ret)
        return ret;

    return scnprintf(buf, PAGE_SIZE, "ok\n");
}

static DEVICE_ATTR_WO(ssd1306_command);
static DEVICE_ATTR_WO(ssd1306_data);
static DEVICE_ATTR_RO(ssd1306_init);

static struct attribute *ssd1306_attrs[] = {
    &dev_attr_ssd1306_command.attr,
    &dev_attr_ssd1306_data.attr,
    &dev_attr_ssd1306_init.attr,
    NULL,
};

static struct attribute_group ssd1306_attr_group = {
    .attrs = ssd1306_attrs,
};

/* ========== misc 标准用法 ========== */

/*
 * 标准 misc 用法：open 时，misc core 会把 file->private_data 设为 struct
 * miscdevice* 你只需要把它 container_of 回你的 ssd1306_data，并重新写回
 * file->private_data。
 */
static int ssd1306_misc_open(struct inode *inode, struct file *file) {
    struct miscdevice *mdev = file->private_data;
    struct ssd1306_data *data;

    if (!mdev)
        return -ENODEV;

    data = container_of(mdev, struct ssd1306_data, miscdev);
    file->private_data = data;
    return 0;
}

static ssize_t ssd1306_misc_write(struct file *file, const char __user *buf,
                                  size_t count, loff_t *ppos) {
    struct ssd1306_data *data = file->private_data;
    u8 *kbuf;
    int ret;

    if (!data || !data->client)
        return -ENODEV;

    if (count == 0)
        return 0;

    kbuf = memdup_user(buf, count);
    if (IS_ERR(kbuf))
        return PTR_ERR(kbuf);

    mutex_lock(&data->lock);
    /* 约定：/dev/ssd1306 的 write() 内容全部当作 data payload 发送 */
    ret = ssd1306_write_data_buf(data->client, kbuf, count);
    mutex_unlock(&data->lock);

    kfree(kbuf);

    if (ret)
        return ret;
    return count;
}

static const struct file_operations ssd1306_misc_fops = {
    .owner = THIS_MODULE,
    .open = ssd1306_misc_open,
    .write = ssd1306_misc_write,
    .llseek = no_llseek,
};

/* ========== i2c driver ========== */

static int ssd1306_probe(struct i2c_client *client,
                         const struct i2c_device_id *id) {
    struct ssd1306_data *data;
    int ret;

    dev_info(&client->dev, "======Probing SSD1306 START======\n");
    dev_info(&client->dev, "I2C Address: 0x%02x, Adapter: %s (bus %d)\n",
             client->addr, client->adapter->name, client->adapter->nr);

    data = devm_kzalloc(&client->dev, sizeof(*data), GFP_KERNEL);
    if (!data) {
        dev_err(&client->dev, "Failed to allocate memory for ssd1306_data\n");
        return -ENOMEM;
    }

    data->client = client;
    mutex_init(&data->lock);
    i2c_set_clientdata(client, data);

    mutex_lock(&data->lock);
    ret = ssd1306_init_display(client);
    mutex_unlock(&data->lock);
    if (ret < 0) {
        dev_err(&client->dev, "Failed to initialize SSD1306 display\n");
        return ret;
    }

    ret = sysfs_create_group(&client->dev.kobj, &ssd1306_attr_group);
    if (ret) {
        dev_err(&client->dev, "Failed to create sysfs group\n");
        return ret;
    }

    data->miscdev.minor = MISC_DYNAMIC_MINOR;
    data->miscdev.name = SSD1306_NAME; /* /dev/ssd1306 */
    data->miscdev.fops = &ssd1306_misc_fops;
    data->miscdev.parent = &client->dev;

    ret = misc_register(&data->miscdev);
    if (ret) {
        dev_err(&client->dev, "Failed to register misc device\n");
        sysfs_remove_group(&client->dev.kobj, &ssd1306_attr_group);
        return ret;
    }

    dev_info(&client->dev, "Sysfs ready and misc node created: /dev/%s\n",
             SSD1306_NAME);
    dev_info(&client->dev, "======Probing SSD1306 SUCCESS======\n");
    return 0;
}

static int ssd1306_remove(struct i2c_client *client) {
    struct ssd1306_data *data = i2c_get_clientdata(client);

    misc_deregister(&data->miscdev);
    sysfs_remove_group(&client->dev.kobj, &ssd1306_attr_group);

    dev_info(&client->dev, "======Removing SSD1306 driver======\n");
    return 0;
}

static const struct i2c_device_id ssd1306_ids[] = {{SSD1306_NAME, 0}, {}};
MODULE_DEVICE_TABLE(i2c, ssd1306_ids);

static const struct of_device_id ssd1306_of_match[] = {
    {
        .compatible = "ssd1306",
    },
    {}};
MODULE_DEVICE_TABLE(of, ssd1306_of_match);

static struct i2c_driver ssd1306_driver = {
    .driver =
        {
            .name = SSD1306_NAME,
            .of_match_table = ssd1306_of_match,
        },
    .probe = ssd1306_probe,
    .remove = ssd1306_remove,
    .id_table = ssd1306_ids,
};

module_i2c_driver(ssd1306_driver);

MODULE_AUTHOR("Cybersyn");
MODULE_DESCRIPTION(
    "SSD1306 I2C OLED Display Driver (sysfs + misc, standard misc open)");
MODULE_LICENSE("GPL");
