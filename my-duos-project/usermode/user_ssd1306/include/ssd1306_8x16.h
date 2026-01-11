#include <stdint.h>

#define SSD1306_W 128
#define SSD1306_H 64
#define SSD1306_PAGES (SSD1306_H / 8)
#define SSD1306_file_buff_SIZE (SSD1306_W * SSD1306_PAGES)

void ssd1306_buffer_clear(uint8_t *file_buff);
void ssd1306_draw_buffer_char8x16(uint8_t *file_buff, int x, int page, char ch);
void ssd1306_draw_buffer_string8x16(uint8_t *file_buff, int x, int page,
                                    const char *s);
