#ifndef _SSD1306_H_
#define _SSD1306_H_

#include <linux/i2c.h>
#include <linux/miscdevice.h>
#include <linux/mutex.h>
#include <linux/types.h>

#define SSD1306_NAME "ssd1306"
#define SSD1306_I2C_CMD 0x00
#define SSD1306_I2C_DATA 0x40
#define SSD1306_WIDTH 128
#define SSD1306_HEIGHT 64

struct ssd1306_data {
    struct i2c_client *client;
    struct mutex lock;
    struct miscdevice miscdev;
};

int ssd1306_write_data_buf(struct i2c_client *client, const u8 *data,
                           size_t len);

#endif // !_SSD1306_H_
