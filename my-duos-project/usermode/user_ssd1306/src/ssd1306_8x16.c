#include "ssd1306_8x16.h"
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#define FONT8x16_IMPLEMENTATION
#include "font8x16_ascii.h"
#include <string.h>

void ssd1306_buffer_clear(uint8_t *file_buff) {
    memset(file_buff, 0x00, SSD1306_file_buff_SIZE);
}

void ssd1306_draw_buffer_char8x16(uint8_t *file_buff, int x, int page,
                                  char ch) {

    if (!(page >= 0 && page + 1 <= 7)) {
        printf("Page set invalid\n");
        return;
    }

    if (x + 7 >= SSD1306_W) {
        printf("x set invalid\n");
        return;
    }
    unsigned char uch = (unsigned char)ch;
    const uint8_t *g = font8x16[uch];

    int col;
    // 行扫描转列扫描
    for (col = 0; col < 8; col++) {
        uint8_t high_8bits_data = 0;
        uint8_t low_8bits_data = 0;
        // high_8bits_data
        for (int row = 0; row < 8; row++) {
            if (g[row] & (1u << (7 - col)))
                high_8bits_data |= (1u << row); // 填入lsb
        }
        // low_8bits_data
        for (int row = 0; row < 8; row++) {
            if (g[8 + row] & (1u << (7 - col)))
                low_8bits_data |= (1u << row);
        }

        file_buff[page * SSD1306_W + x + col] = high_8bits_data;
        file_buff[(page + 1) * SSD1306_W + x + col] = low_8bits_data;
    }
}

void ssd1306_draw_buffer_string8x16(uint8_t *file_buff, int x, int page,
                                    const char *s) {
    while (*s) {
        ssd1306_draw_buffer_char8x16(file_buff, x, page, *s++);
        x += 8;
        if (x > SSD1306_W - 8)
            break;
    }
}
