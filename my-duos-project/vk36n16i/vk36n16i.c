#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define I2C_DEV_PATH "/dev/i2c-4"
#define VK36N16I_I2C_ADDR 0x65

#define VK36N16I_KEY_BYTES 2
#define VK36N16I_KEY_COUNT 16

/* ============================================================
 * 键值查表 - 高效处理键值映射
 * 0x0001 -> 1, 0x0002 -> 4, 0x0004 -> 7...
 * ============================================================ */
static const uint8_t key_value_table[16] = {
    1,  // 0x0001 (bit 0)
    4,  // 0x0002 (bit 1)
    7,  // 0x0004 (bit 2)
    15, // 0x0008 (bit 3)
    2,  // 0x0010 (bit 4)
    5,  // 0x0020 (bit 5)
    8,  // 0x0040 (bit 6)
    0,  // 0x0080 (bit 7)
    3,  // 0x0100 (bit 8)
    6,  // 0x0200 (bit 9)
    9,  // 0x0400 (bit 10)
    12, // 0x0800 (bit 11)
    10, // 0x1000 (bit 12)
    13, // 0x2000 (bit 13)
    11, // 0x4000 (bit 14)
    14  // 0x8000 (bit 15)
};

/**
 * 获取键值对应的逻辑键编号
 * 参数:  hw_key - 硬件键值 (0x0001-0x8000)
 * 返回: 逻辑键编号 (0-15)，无效返回 0xFF
 */
static uint8_t vk36n16i_get_key_value(uint16_t hw_key) {
    int bit_pos = __builtin_ctz(hw_key); // 获取最低位位置

    if (hw_key == 0 || bit_pos >= 16) {
        return 0xFF; // 无效键值
    }

    return key_value_table[bit_pos];
}

static int vk36n16i_read_key_data(int fd, uint8_t *keys) {
    if (ioctl(fd, I2C_SLAVE, VK36N16I_I2C_ADDR) < 0) {
        perror("ioctl I2C_SLAVE");
        return -1;
    }
    if (read(fd, keys, 2) != 2) {
        perror("read");
        return -1;
    }
    return 0;
}
static int vk36n16i_key_value_process(int fd, uint16_t *keys) {
    // Placeholder for processing key values
    uint8_t key[2];
    uint16_t key_return;
    if (vk36n16i_read_key_data(fd, key) < 0) {
        return -1;
    }
    key_return = (key[1] << 8) | key[0];
    *keys = key_return;
    return 0;
}

int main(void) {
    uint16_t keys; // 修正:  应该是变量而不是指针
    int fd = open(I2C_DEV_PATH, O_RDWR);
    if (fd < 0) {
        perror("open i2c");
        return 1;
    }

    printf("Reading VK36N16I keyboard from %s (addr: 0x%02X)\n", I2C_DEV_PATH,
           VK36N16I_I2C_ADDR);
    printf("Press Ctrl+C to exit\n\n");

    while (1) {
        vk36n16i_key_value_process(fd, &keys);
        uint8_t logic_key = vk36n16i_get_key_value(keys);

        if (logic_key != 0xFF) {
            printf("HW Key: 0x%04X -> Logic Key: %d\n", keys, logic_key);
        } else {
            printf("Invalid key:  0x%04X\n", keys);
        }
        sleep(1);
    }
    close(fd);
    return 0;
}
