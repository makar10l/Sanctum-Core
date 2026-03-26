#ifndef SSD1315
#define SSD1315
#include <stdint.h>
#include <i2c.h>

typedef struct{
    i2c_device_t I2C_device;
    uint8_t contrast;
    uint8_t command_buffer[2];
} ssd1315_display_t;

int8_t ssd1315_display_on(ssd1315_display_t* disp);
int8_t ssd1315_display_off(ssd1315_display_t* disp);
int8_t ssd1315_display_setcontrast(ssd1315_display_t* disp, uint8_t contrast);
int8_t ssd1315_display_update(ssd1315_display_t* disp);
int8_t ssd1315_display_init(ssd1315_display_t* disp, uint8_t addr, uint8_t* buffer);

extern const uint8_t ssd1315_init_buffer[];
#endif