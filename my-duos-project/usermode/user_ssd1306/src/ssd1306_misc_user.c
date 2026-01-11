#include "ssd1306_8x16.h"
#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define DEV_PATH "/dev/ssd1306"
#define WIDTH 128
#define HEIGHT 64
#define FB_SIZE (WIDTH * HEIGHT / 8)

static int write_all(int fd, const void *buf, size_t len) {
    const uint8_t *p = (const uint8_t *)buf;
    size_t left = len;

    while (left > 0) {
        ssize_t n = write(fd, p, left);
        printf("write %zu bytes, n=%zd\n", left, n);
        if (n < 0) {
            if (errno == EINTR)
                continue;
            return -1;
        }
        p += (size_t)n;
        left -= (size_t)n;
    }
    return 0;
}

static void pattern_all(uint8_t *fb, uint8_t v) { memset(fb, v, FB_SIZE); }

static void pattern_checker(uint8_t *fb) {
    for (int page = 0; page < 8; page++) {
        for (int x = 0; x < WIDTH; x++)
            fb[page * WIDTH + x] = (x & 1) ? 0xCC : 0x00;
    }
}

static void pattern_bars(uint8_t *fb) {
    memset(fb, 0x00, FB_SIZE);
    memset(fb + 0 * WIDTH, 0xFF, WIDTH);
    memset(fb + 1 * WIDTH, 0xFF, WIDTH);
}

int main(int argc, char **argv) {
    uint8_t fb[FB_SIZE];
    const char *mode = (argc >= 2) ? argv[1] : "checker";
    const char *select = (argc >= 3) ? argv[2] : NULL;

    if (strcmp(mode, "on") == 0) {
        pattern_all(fb, 0xFF);
    } else if (strcmp(mode, "off") == 0) {
        pattern_all(fb, 0x00);
    } else if (strcmp(mode, "bars") == 0) {
        pattern_bars(fb);
    } else if (strcmp(mode, "user") == 0) {
        if (!select) {
            fprintf(stderr, "usage: %s user 1|2\n", argv[0]);
            return 1;
        }

        if (strcmp(select, "1") == 0) {
            printf("user pattern 1 selected\n");
            ssd1306_buffer_clear(fb);
            ssd1306_draw_buffer_string8x16(fb, 0, 0, "Hellow, world!");
            ssd1306_draw_buffer_string8x16(fb, 0, 2, "Form cybersyn.");
        } else if (strcmp(select, "2") == 0) {
            printf("user pattern 2 selected\n");
            pattern_all(fb, 0x0F);
        } else {
            fprintf(stderr, "unknown user pattern: %s (use 1 or 2)\n", select);
            return 1;
        }
    } else {
        pattern_checker(fb);
    }

    int fd = open(DEV_PATH, O_WRONLY);
    // open返回文件描述符，小于0表示打开失败
    if (fd < 0) {
        fprintf(stderr, "open(%s) failed: %s\n", DEV_PATH, strerror(errno));
        return 1;
    }

    if (write_all(fd, fb, sizeof(fb)) != 0) {
        fprintf(stderr, "write failed: %s\n", strerror(errno));
        close(fd);
        return 1;
    }

    close(fd);
    return 0;
}
