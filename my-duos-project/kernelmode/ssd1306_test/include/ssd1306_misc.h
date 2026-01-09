#ifndef _SSD1306_MISC_H_
#define _SSD1306_MISC_H_

struct ssd1306_data;

/*
 * Register / deregister misc device (/dev/ssd1306).
 *
 * Call ssd1306_misc_register() in probe() after data->client and mutex init.
 * Call ssd1306_misc_deregister() in remove().
 */
int ssd1306_misc_register(struct ssd1306_data *data);
void ssd1306_misc_deregister(struct ssd1306_data *data);

#endif /* _SSD1306_MISC_H_ */
