#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define DEV_PATH "/dev/ssd1306"
#define WIDTH 128
#define HEIGHT 64
#define FB_SIZE (WIDTH * HEIGHT / 8) /* 1024 */

static int write_all(int fd, const void *buf, size_t len) {
    const uint8_t *p = (const uint8_t *)buf;
    size_t left = len;

    while (left > 0) {
        ssize_t n = write(fd, p, left);
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
    /* 8 pages, each 128 bytes */
    for (int page = 0; page < 8; page++) {
        for (int x = 0; x < WIDTH; x++) {
            /* 0xAA / 0x55 形成棋盘格感觉 */
            fb[page * WIDTH + x] = (x & 1) ? 0xAA : 0x55;
        }
    }
}

static void pattern_bars(uint8_t *fb) {
    memset(fb, 0x00, FB_SIZE);
    /* 点亮前两页形成两条横带 */
    memset(fb + 0 * WIDTH, 0xFF, WIDTH);
    memset(fb + 1 * WIDTH, 0xFF, WIDTH);
}

int main(int argc, char **argv) {
    uint8_t fb[FB_SIZE];
    const char *mode = (argc >= 2) ? argv[1] : "checker";

    if (strcmp(mode, "on") == 0) {
        pattern_all(fb, 0xFF);
    } else if (strcmp(mode, "off") == 0) {
        pattern_all(fb, 0x00);
    } else if (strcmp(mode, "bars") == 0) {
        pattern_bars(fb);
    } else {
        /* 默认 checker */
        pattern_checker(fb);
    }

    int fd = open(DEV_PATH, O_WRONLY);
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
    printf("Wrote %u bytes to %s (pattern=%s)\n", (unsigned)sizeof(fb),
           DEV_PATH, mode);
    printf("Try: %s on|off|checker|bars\n", argv[0]);
    return 0;
}
