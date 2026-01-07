#include <linux/device.h>
#include <linux/i2c.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/mutex.h>
#include <linux/sysfs.h>

#define TM1650_NAME "tm1650"

/* TM1650 地址（这些是 7 位 I²C 地址） */
#define TM1650_ADDR_CMD 0x24
#define TM1650_ADDR_DIG1 0x34
#define TM1650_ADDR_DIG2 0x35
#define TM1650_ADDR_DIG3 0x36
#define TM1650_ADDR_DIG4 0x37

/* 7 段编码表 */
static const uint8_t segment_code[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D,
                                       0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C,
                                       0x39, 0x5E, 0x79, 0x71};

/* 驱动私有数据结构 */
struct tm1650_data {
    struct i2c_client *client;
    uint8_t brightness;
    uint8_t display[4];
    struct mutex lock;
};

/**
 * 向 TM1650 写一个字节
 *
 * TM1650 的协议：直接向某个地址写 1 个字节的数据
 * 不是"寄存器地址 + 数据"的格式
 */
static int tm1650_write_byte(struct i2c_client *client, uint8_t addr,
                             uint8_t data) {
    struct i2c_msg msg;
    int ret;

    dev_dbg(&client->dev, "write:  addr=0x%02x, data=0x%02x\n", addr, data);

    /* 构造 I²C 消息 */
    msg.addr = addr; /* 从机地址 */
    msg.flags = 0;   /* 写操作 */
    msg.len = 1;     /* 只发 1 个字节 */
    msg.buf = &data; /* 数据缓冲区 */

    ret = i2c_transfer(client->adapter, &msg, 1);

    if (ret != 1) {
        dev_err(&client->dev, "write to addr 0x%02x failed:  %d\n", addr, ret);
        return -EIO;
    }

    return 0;
}

/**
 * 从 TM1650 读一个字节
 */
static int tm1650_read_byte(struct i2c_client *client, uint8_t addr,
                            uint8_t *data) {
    struct i2c_msg msg;
    uint8_t buf;
    int ret;

    dev_dbg(&client->dev, "read: addr=0x%02x\n", addr);

    /* 读操作：直接从地址读 1 个字节 */
    msg.addr = addr;
    msg.flags = I2C_M_RD; /* 读标志 */
    msg.len = 1;
    msg.buf = &buf;

    ret = i2c_transfer(client->adapter, &msg, 1);

    if (ret != 1) {
        dev_err(&client->dev, "read from addr 0x%02x failed: %d\n", addr, ret);
        return -EIO;
    }

    *data = buf;
    return 0;
}

/**
 * 初始化 TM1650
 */
static int tm1650_init(struct tm1650_data *data) {
    uint8_t cmd;
    int ret;

    /* 构建命令字
     * bit7-bit4:  保留或亮度
     * bit3: 显示开关（1=开）
     * bit2-bit0: 亮度（0-7）
     */
    cmd = 0x80;                              /* 基础命令 */
    cmd |= ((data->brightness & 0x07) << 4); /* 设置亮度 */
    cmd |= 0x01;                             /* 使能显示 */

    ret = tm1650_write_byte(data->client, TM1650_ADDR_CMD, cmd);
    if (ret < 0) {
        dev_err(&data->client->dev, "init failed\n");
        return ret;
    }

    dev_info(&data->client->dev, "TM1650 initialized, brightness=%u\n",
             data->brightness);
    return 0;
}

/**
 * 显示一个数字（0-15）在指定位置（0-3）
 */
static int tm1650_display_digit(struct tm1650_data *data, int pos, int digit) {
    uint8_t addrs[] = {TM1650_ADDR_DIG1, TM1650_ADDR_DIG2, TM1650_ADDR_DIG3,
                       TM1650_ADDR_DIG4};
    uint8_t code;
    int ret;

    if (pos < 0 || pos > 3 || digit < 0 || digit > 15)
        return -EINVAL;

    code = segment_code[digit];

    mutex_lock(&data->lock);
    ret = tm1650_write_byte(data->client, addrs[pos], code);
    if (ret == 0)
        data->display[pos] = digit;
    mutex_unlock(&data->lock);

    return ret;
}

/**
 * 清除所有显示
 */
static int tm1650_clear_display(struct tm1650_data *data) {
    int i;

    for (i = 0; i < 4; i++) {
        tm1650_display_digit(data, i, 0);
    }

    return 0;
}

/* ============= sysfs 属性接口 ============= */

/**
 * brightness 属性：读取/设置亮度
 */
static ssize_t brightness_show(struct device *dev,
                               struct device_attribute *attr, char *buf) {
    struct i2c_client *client = to_i2c_client(dev);
    struct tm1650_data *data = i2c_get_clientdata(client);

    return sprintf(buf, "%u\n", data->brightness);
}

static ssize_t brightness_store(struct device *dev,
                                struct device_attribute *attr, const char *buf,
                                size_t count) {
    struct i2c_client *client = to_i2c_client(dev);
    struct tm1650_data *data = i2c_get_clientdata(client);
    uint8_t brightness;

    if (kstrtou8(buf, 10, &brightness) < 0)
        return -EINVAL;

    if (brightness > 7)
        brightness = 7;

    mutex_lock(&data->lock);
    data->brightness = brightness;
    mutex_unlock(&data->lock);

    tm1650_init(data);

    return count;
}

/**
 * display 属性：显示 4 位数字
 * 格式：echo "1 2 3 4" > display
 */
static ssize_t display_show(struct device *dev, struct device_attribute *attr,
                            char *buf) {
    struct i2c_client *client = to_i2c_client(dev);
    struct tm1650_data *data = i2c_get_clientdata(client);

    return sprintf(buf, "%d %d %d %d\n", data->display[0], data->display[1],
                   data->display[2], data->display[3]);
}

static ssize_t display_store(struct device *dev, struct device_attribute *attr,
                             const char *buf, size_t count) {
    struct i2c_client *client = to_i2c_client(dev);
    struct tm1650_data *data = i2c_get_clientdata(client);
    int d0, d1, d2, d3;

    if (sscanf(buf, "%d %d %d %d", &d0, &d1, &d2, &d3) != 4)
        return -EINVAL;

    tm1650_display_digit(data, 0, d0);
    tm1650_display_digit(data, 1, d1);
    tm1650_display_digit(data, 2, d2);
    tm1650_display_digit(data, 3, d3);

    return count;
}

/**
 * clear 属性：清除显示
 */
static ssize_t clear_store(struct device *dev, struct device_attribute *attr,
                           const char *buf, size_t count) {
    struct i2c_client *client = to_i2c_client(dev);
    struct tm1650_data *data = i2c_get_clientdata(client);

    tm1650_clear_display(data);

    return count;
}

/* 定义 sysfs 属性 */
static DEVICE_ATTR_RW(brightness);
static DEVICE_ATTR_RW(display);
static DEVICE_ATTR_WO(clear);

static struct attribute *tm1650_attrs[] = {&dev_attr_brightness.attr,
                                           &dev_attr_display.attr,
                                           &dev_attr_clear.attr, NULL};

static struct attribute_group tm1650_attr_group = {
    .attrs = tm1650_attrs,
};

/* ============= I²C 驱动回调 ============= */

/**
 * probe 函数：当有 TM1650 设备被枚举时调用
 */
static int tm1650_probe(struct i2c_client *client,
                        const struct i2c_device_id *id) {
    struct tm1650_data *data;
    int ret;

    dev_info(&client->dev, "===== TM1650 PROBE START =====\n");
    dev_info(&client->dev, "addr:  0x%02x, adapter: %s (bus %d)\n",
             client->addr, client->adapter->name, client->adapter->nr);

    /* 分配驱动私有数据 */
    data = devm_kzalloc(&client->dev, sizeof(struct tm1650_data), GFP_KERNEL);
    if (!data) {
        dev_err(&client->dev, "Failed to allocate memory\n");
        return -ENOMEM;
    }
    dev_info(&client->dev, "Memory allocated\n");

    data->client = client;
    data->brightness = 7; /* 默认最亮 */
    mutex_init(&data->lock);

    /* 绑定驱动数据到设备 */
    i2c_set_clientdata(client, data);
    dev_info(&client->dev, "Client data set\n");

    /* 初始化硬件 */
    ret = tm1650_init(data);
    if (ret < 0) {
        dev_err(&client->dev, "tm1650_init failed:  %d\n", ret);
        return ret;
    }
    dev_info(&client->dev, "Hardware initialized\n");

    /* 清除显示 */
    tm1650_clear_display(data);
    dev_info(&client->dev, "Display cleared\n");

    /* 创建 sysfs 属性 */
    dev_info(&client->dev, "Creating sysfs group.. .\n");
    ret = sysfs_create_group(&client->dev.kobj, &tm1650_attr_group);
    if (ret < 0) {
        dev_err(&client->dev, "sysfs_create_group failed:  %d\n", ret);
        return ret;
    }
    dev_info(&client->dev, "Sysfs group created\n");

    dev_info(&client->dev, "===== TM1650 PROBE SUCCESS =====\n");
    return 0;
}

/**
 * remove 函数：当设备被移除时调用
 */
static int tm1650_remove(struct i2c_client *client) {
    struct tm1650_data *data = i2c_get_clientdata(client);

    dev_info(&client->dev, "===== TM1650 REMOVE =====\n");

    /* 删除 sysfs 属性 */
    sysfs_remove_group(&client->dev.kobj, &tm1650_attr_group);

    /* 清除显示 */
    tm1650_clear_display(data);

    dev_info(&client->dev, "===== TM1650 REMOVED =====\n");
    return 0;
}

/* I2C 设备 ID 表 */
static const struct i2c_device_id tm1650_ids[] = {{TM1650_NAME, 0}, {}};
MODULE_DEVICE_TABLE(i2c, tm1650_ids);

/* 设备树兼容性表 */
static const struct of_device_id tm1650_of_match[] = {
    {.compatible = "titanmicro,tm1650"}, {}};
MODULE_DEVICE_TABLE(of, tm1650_of_match);

/* I2C 驱动结构 */
static struct i2c_driver tm1650_driver = {
    .driver =
        {
            .name = TM1650_NAME,
            .of_match_table = tm1650_of_match,
        },
    .probe = tm1650_probe,
    .remove = tm1650_remove,
    .id_table = tm1650_ids,
};

/* 模块初始化 */
module_i2c_driver(tm1650_driver);

MODULE_AUTHOR("Cybersyn");
MODULE_DESCRIPTION("TM1650 LED Display Driver for Milk-V DuoS");
MODULE_LICENSE("GPL");
