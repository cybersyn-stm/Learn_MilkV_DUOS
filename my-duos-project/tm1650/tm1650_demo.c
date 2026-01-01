#include <errno.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define I2C_DEV_PATH "/dev/i2c-5"

#define TM1650_ADDR_CMD 0x24
#define TM1650_ADDR_DIG1 0x34
#define TM1650_ADDR_DIG2 0x35
#define TM1650_ADDR_DIG3 0x36
#define TM1650_ADDR_DIG4 0x37

static uint8_t tm1650_build_data_cmd_mode(void) {
  uint8_t cmd = 0;
  cmd |= (0 << 7);
  cmd |= (1 << 6);
  cmd |= (0 << 5);
  cmd |= (0 << 4);
  return cmd; // 0x40
}

static uint8_t tm1650_build_display_cmd(uint8_t brightness, int enable) {
  if (brightness > 7)
    brightness = 7;
  uint8_t cmd = 0x88 | (brightness & 0x07);
  if (!enable)
    cmd &= ~0x01;
  return cmd;
}

static const uint8_t seg_code[16] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d,
                                     0x7d, 0x07, 0x7f, 0x6f, 0x77, 0x7c,
                                     0x39, 0x5e, 0x79, 0x71};

static int i2c_write_byte(int fd, uint8_t addr7, uint8_t data) {
  if (ioctl(fd, I2C_SLAVE, addr7) < 0) {
    fprintf(stderr, "ioctl I2C_SLAVE addr 0x%02X failed: %s\n", addr7,
            strerror(errno));
    return -1;
  }
  int ret = write(fd, &data, 1);
  if (ret != 1) {
    fprintf(stderr, "write to addr 0x%02X failed: %s\n", addr7,
            strerror(errno));
    return -1;
  }
  return 0;
}

static int tm1650_init(int fd, uint8_t brightness) {
  int ret;
  uint8_t data_cmd = tm1650_build_data_cmd_mode();
  uint8_t disp_cmd = tm1650_build_display_cmd(brightness, 1);
  ret = i2c_write_byte(fd, TM1650_ADDR_CMD, data_cmd);
  if (ret < 0)
    return ret;
  ret = i2c_write_byte(fd, TM1650_ADDR_CMD, disp_cmd);
  return ret;
}

static int tm1650_display_digits(int fd, int d0, int d1, int d2, int d3) {
  int ret;
  uint8_t bytes[4];
  bytes[0] = seg_code[d0 & 0x0F];
  bytes[1] = seg_code[d1 & 0x0F];
  bytes[2] = seg_code[d2 & 0x0F];
  bytes[3] = seg_code[d3 & 0x0F];

  if ((ret = i2c_write_byte(fd, TM1650_ADDR_DIG1, bytes[0])) < 0)
    return ret;
  if ((ret = i2c_write_byte(fd, TM1650_ADDR_DIG2, bytes[1])) < 0)
    return ret;
  if ((ret = i2c_write_byte(fd, TM1650_ADDR_DIG3, bytes[2])) < 0)
    return ret;
  if ((ret = i2c_write_byte(fd, TM1650_ADDR_DIG4, bytes[3])) < 0)
    return ret;
  return 0;
}

static int tm1650_display_number(int fd, int value) {
  if (value < 0)
    value = -value;
  if (value > 9999)
    value = 9999;
  int d3 = value % 10;
  value /= 10;
  int d2 = value % 10;
  value /= 10;
  int d1 = value % 10;
  value /= 10;
  int d0 = value % 10;
  return tm1650_display_digits(fd, d0, d1, d2, d3);
}

int main(void) {
  int fd = open(I2C_DEV_PATH, O_RDWR);
  if (fd < 0) {
    perror("open " I2C_DEV_PATH);
    return 1;
  }

  printf("TM1650 demo on %s\n", I2C_DEV_PATH);
  if (tm1650_init(fd, 7) < 0) {
    close(fd);
    return 1;
  }
  if (tm1650_display_digits(fd, 1, 2, 3, 4) < 0) {
    close(fd);
    return 1;
  }
  printf("Display 1234.\n");
  sleep(2);

  for (int i = 0; i <= 20; i++) {
    if (tm1650_display_number(fd, i) < 0) {
      close(fd);
      return 1;
    }
    usleep(300 * 1000);
  }

  uint8_t off_cmd = tm1650_build_display_cmd(0, 0);
  i2c_write_byte(fd, TM1650_ADDR_CMD, off_cmd);
  printf("Turn display off.\n");
  close(fd);
  return 0;
}
