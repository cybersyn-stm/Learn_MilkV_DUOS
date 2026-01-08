#include <linux/device.h>
#include <linux/i2c.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/mutex.h>
#include <linux/sysfs.h>

#define SSD1306_NAME "ssd1306"
#define SSD1306_I2C_ADDRESS 0x3C // 请结合你硬件实际地址选择
#define SSD1306_I2C_CMD 0x00     // 控制字节: 命令
#define SSD1306_I2C_DATA 0x40    // 控制字节: 数据
#define SSD1306_WIDTH 128
#define SSD1306_HEIGHT 64

struct ssd1306_data {
    struct i2c_client *client;
    struct mutex lock;
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
    ret |= ssd1306_write_command(client, 0xAE); // Display ON

    if (ret != 0) {
        dev_err(&client->dev, "SSD1306 initialization sequence failed\n");
        return -EIO;
    }
    return 0;
}

static int ssd1306_probe(struct i2c_client *client,
                         const struct i2c_device_id *id) {
    struct ssd1306_data *data;
    int ret;

    dev_info(&client->dev, "======Probing SSD1306 START======");
    dev_info(&client->dev, "I2C Address: 0x%02x, Adapter: %s (bus %d)",
             client->addr, client->adapter->name, client->adapter->nr);

    data = devm_kzalloc(&client->dev, sizeof(struct ssd1306_data), GFP_KERNEL);
    if (!data) {
        dev_err(&client->dev, "Failed to allocate memory for ssd1306_data\n");
        return -ENOMEM;
    }

    data->client = client;
    mutex_init(&data->lock);
    i2c_set_clientdata(client, data);

    ret = ssd1306_init_display(client);
    if (ret < 0) {
        dev_err(&client->dev, "Failed to initialize SSD1306 display\n");
        return ret;
    }
    dev_info(&client->dev, "SSD1306 display initialized successfully");
    dev_info(&client->dev, "======Probing SSD1306 SUCCESS======");

    return 0;
}

static int ssd1306_remove(struct i2c_client *client) {
    dev_info(&client->dev, "======Removing SSD1306 driver======");
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
MODULE_DESCRIPTION("SSD1306 I2C OLED Display Driver (fixed version)");
MODULE_LICENSE("GPL");
