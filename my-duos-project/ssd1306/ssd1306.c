#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define I2C_DEV_PATH "/dev/i2c-5"

#define SSD1306_I2C_ADDR 0x3C
#define SSD1306_I2C_CMD 0x00
#define SSD1306_I2C_DATA 0x40
#define SSD1306_WIDTH 128
#define SSD1306_HEIGHT 64

static int ssd1306_write_command(int fd, uint8_t command) {
    uint8_t buffer[2];
    buffer[0] = SSD1306_I2C_CMD;
    buffer[1] = command;
    if (ioctl(fd, I2C_SLAVE, SSD1306_I2C_ADDR) < 0) {
        perror("Failed to set I2C slave address");
        return -1;
    }
    if (write(fd, buffer, 2) != 2) {
        perror("Failed to write command to SSD1306");
        return -1;
    }
    return 0;
}
static int ssd1306_init_display(int fd) {

    printf("Init SSD1306\n");
    ssd1306_write_command(fd, 0xAE);
    ssd1306_write_command(fd, 0x20);
    ssd1306_write_command(fd, 0xC8);
    ssd1306_write_command(fd, 0xDA);
    ssd1306_write_command(fd, 0x81);
    ssd1306_write_command(fd, 0xD9);
    ssd1306_write_command(fd, 0xDB);
    ssd1306_write_command(fd, 0x8D);
    ssd1306_write_command(fd, 0xA4);
    ssd1306_write_command(fd, 0xAF);
    return 0;
}
int main() {
    int fd = open(I2C_DEV_PATH, O_RDWR);
    if (fd < 0) {
        perror("Failed to open I2C device");
        return EXIT_FAILURE;
    }
    // init_ssd1306
    ssd1306_init_display(fd);
    return 0;
}
