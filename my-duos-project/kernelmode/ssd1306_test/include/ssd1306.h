#pragma once

#include <linux/i2c.h>
#include <linux/miscdevice.h>
#include <linux/mutex.h>
#include <linux/types.h>

/* Driver name / device node name */
#define SSD1306_NAME "ssd1306"

/* SSD1306 I2C control bytes */
#define SSD1306_I2C_CMD 0x00
#define SSD1306_I2C_DATA 0x40

/* Panel geometry (your module assumes 128x64) */
#define SSD1306_WIDTH 128
#define SSD1306_HEIGHT 64
#define SSD1306_PAGES (SSD1306_HEIGHT / 8)
#define SSD1306_FB_SIZE (SSD1306_WIDTH * SSD1306_PAGES)

struct ssd1306_data {
    struct i2c_client *client;
    struct mutex lock;
    struct miscdevice miscdev;
};

/* Core helpers used by misc layer */
int ssd1306_write_cmd(struct i2c_client *client, u8 cmd);
int ssd1306_set_full_window(struct i2c_client *client);
int ssd1306_write_data_buf(struct i2c_client *client, const u8 *data,
                           size_t len);
