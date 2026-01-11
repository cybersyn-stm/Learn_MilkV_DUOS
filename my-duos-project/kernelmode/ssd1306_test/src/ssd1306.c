#include <linux/device.h>
#include <linux/i2c.h>
#include <linux/kernel.h>
#include <linux/mutex.h>
#include <linux/slab.h>
#include <linux/string.h>
#include <linux/sysfs.h>
#include <linux/types.h>

#include "linux/module.h"
#include "ssd1306.h"
#include "ssd1306_misc.h"

/* 发送命令/数据的底层函数：每次发送 (control + data) 两字节 */
static int ssd1306_write_byte(struct i2c_client *client, u8 control, u8 data) {
    u8 buf[2];
    struct i2c_msg msg;
    int ret;

    buf[0] = control; /* 0x00=命令, 0x40=数据 */
    buf[1] = data;

    msg.addr = client->addr;
    msg.flags = 0;
    msg.len = sizeof(buf);
    msg.buf = buf;

    ret = i2c_transfer(client->adapter, &msg, 1);
    if (ret < 1) {
        dev_err(&client->dev, "i2c_transfer failed: %d\n", ret);
        return -EIO;
    }
    return 0;
}

/* 对外可见：发送 1 字节命令 */
int ssd1306_write_cmd(struct i2c_client *client, u8 cmd) {
    return ssd1306_write_byte(client, SSD1306_I2C_CMD, cmd);
}

/*
 * 对外可见：设置整屏写入窗口
 * 0x20 0x00 : Horizontal Addressing Mode
 * 0x21 0..127 : Column range
 * 0x22 0..7   : Page range (for 64px height)
 */
int ssd1306_set_full_window(struct i2c_client *client) {
    int ret = 0;

    ret |= ssd1306_write_cmd(client, 0x20);
    ret |= ssd1306_write_cmd(client, 0x00);

    ret |= ssd1306_write_cmd(client, 0x21);
    ret |= ssd1306_write_cmd(client, 0x00);
    ret |= ssd1306_write_cmd(client, 0x7F);

    ret |= ssd1306_write_cmd(client, 0x22);
    ret |= ssd1306_write_cmd(client, 0x00);
    ret |= ssd1306_write_cmd(client, 0x07);

    return ret ? -EIO : 0;
}

/*
 * 一次性发送 data payload（前面自动加 0x40 控制字节）
 * 给 misc 层 write() 调用，所以必须是“非 static”
 */
int ssd1306_write_data_buf(struct i2c_client *client, const u8 *data,
                           size_t len) {
    struct i2c_msg msg;
    u8 *buf;
    int ret;

    if (!client || !data)
        return -EINVAL;
    if (len == 0)
        return 0;

    buf = kmalloc(len + 1, GFP_KERNEL);
    if (!buf)
        return -ENOMEM;

    buf[0] = SSD1306_I2C_DATA; /* 控制字节: 数据 */
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

static int ssd1306_write_data_byte(struct i2c_client *client, u8 data) {
    return ssd1306_write_byte(client, SSD1306_I2C_DATA, data);
}

/* SSD1306 初始化命令序列 */
static int ssd1306_init_display(struct i2c_client *client) {
    int ret = 0;

    ret |= ssd1306_write_cmd(client, 0xAE); /* Display OFF */
    ret |= ssd1306_write_cmd(client, 0x20); /* Set Memory Addressing Mode */
    ret |= ssd1306_write_cmd(client, 0x00); /* Horizontal Addressing Mode */
    ret |= ssd1306_write_cmd(client, 0xB0); /* Set Page Start Address 0 */
    ret |= ssd1306_write_cmd(client, 0xC8); /* COM Output Scan Direction */
    ret |= ssd1306_write_cmd(client, 0x00); /* Set low column address */
    ret |= ssd1306_write_cmd(client, 0x10); /* Set high column address */
    ret |= ssd1306_write_cmd(client, 0x40); /* Set start line address */
    ret |= ssd1306_write_cmd(client, 0x81); /* Set contrast control */
    ret |= ssd1306_write_cmd(client, 0xFF);
    ret |= ssd1306_write_cmd(client, 0xA1); /* Set segment re-map 0..127 */
    ret |= ssd1306_write_cmd(client, 0xA6); /* Normal display */
    ret |= ssd1306_write_cmd(client, 0xA8); /* Set multiplex ratio */
    ret |= ssd1306_write_cmd(client, 0x3F);
    ret |= ssd1306_write_cmd(client, 0xA4); /* Output RAM to display */
    ret |= ssd1306_write_cmd(client, 0xD3); /* Set display offset */
    ret |= ssd1306_write_cmd(client, 0x00); /* No offset */
    ret |= ssd1306_write_cmd(client, 0xD5); /* Set clock divide ratio */
    ret |= ssd1306_write_cmd(client, 0xF0);
    ret |= ssd1306_write_cmd(client, 0xD9); /* Set pre-charge period */
    ret |= ssd1306_write_cmd(client, 0x22);
    ret |= ssd1306_write_cmd(client, 0xDA); /* Set COM pins config */
    ret |= ssd1306_write_cmd(client, 0x12);
    ret |= ssd1306_write_cmd(client, 0xDB); /* Set vcomh */
    ret |= ssd1306_write_cmd(client, 0x20); /* 0.77xVcc */
    ret |= ssd1306_write_cmd(client, 0x8D); /* DC-DC enable */
    ret |= ssd1306_write_cmd(client, 0x14);
    ret |= ssd1306_write_cmd(client, 0xAF); /* Display ON */

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
    u8 command;
    int ret;

    if (sscanf(buf, "%hhx", &command) != 1) {
        dev_err(dev, "Invalid command format\n");
        return -EINVAL;
    }

    mutex_lock(&data->lock);
    ret = ssd1306_write_cmd(client, command);
    mutex_unlock(&data->lock);

    return ret ? ret : count;
}

static ssize_t ssd1306_data_store(struct device *dev,
                                  struct device_attribute *attr,
                                  const char *buf, size_t count) {
    struct i2c_client *client = to_i2c_client(dev);
    struct ssd1306_data *data = i2c_get_clientdata(client);
    u8 v;
    int ret;

    if (sscanf(buf, "%hhx", &v) != 1) {
        dev_err(dev, "Invalid data format\n");
        return -EINVAL;
    }

    mutex_lock(&data->lock);
    ret = ssd1306_write_data_byte(client, v);
    mutex_unlock(&data->lock);

    return ret ? ret : count;
}

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

    ret = ssd1306_misc_register(data);
    if (ret) {
        sysfs_remove_group(&client->dev.kobj, &ssd1306_attr_group);
        return ret;
    }

    dev_info(&client->dev, "======Probing SSD1306 SUCCESS======\n");
    return 0;
}

static int ssd1306_remove(struct i2c_client *client) {
    struct ssd1306_data *data = i2c_get_clientdata(client);

    if (data)
        ssd1306_misc_deregister(data);

    sysfs_remove_group(&client->dev.kobj, &ssd1306_attr_group);

    dev_info(&client->dev, "======Removing SSD1306 driver======\n");
    return 0;
}

static const struct i2c_device_id ssd1306_ids[] = {{SSD1306_NAME, 0}, {}};
MODULE_DEVICE_TABLE(i2c, ssd1306_ids);
static const struct of_device_id ssd1306_of_match[] = {
    {.compatible = "ssd1306"}, {}};
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
MODULE_DESCRIPTION("SSD1306 I2C OLED Display Driver (sysfs + misc)");
MODULE_LICENSE("GPL");
