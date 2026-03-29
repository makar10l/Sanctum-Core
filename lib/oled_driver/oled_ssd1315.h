#ifndef SSD1315
#define SSD1315
#include <stdint.h>
#include <i2c.h>
#define DISPLAY_BUFFER_SIZE 1024
typedef struct{
    i2c_device_t I2C_device;
    uint8_t contrast;
    uint8_t data_buffer[DISPLAY_BUFFER_SIZE];
} ssd1315_display_t;

int8_t ssd1315_display_on(ssd1315_display_t* disp);
int8_t ssd1315_display_off(ssd1315_display_t* disp);
int8_t ssd1315_display_setcontrast(ssd1315_display_t* disp, uint8_t contrast);
int8_t ssd1315_display_update(ssd1315_display_t* disp);
int8_t ssd1315_display_init(ssd1315_display_t* disp, uint8_t addr);
int8_t ssd1315_display_setpix(ssd1315_display_t* disp, uint8_t x, uint8_t y, uint8_t state);

extern const uint8_t ssd1315_init_buffer[];
#endif