#include <oled_ssd1315.h>
#include <config.h>
#include <i2c.h>
const uint8_t ssd1315_init_buffer[] = {
    0x00,
    0xAE,        // Display OFF
    0x8D, 0x14,  // charge pump
    0xA8, 0x3F,  // Multiplex Ratio
    0xD3, 0x00,  // Display Offset
    0x40,        // Display Start Line
    0xA1,        // Segment Remap
    0xC8,        // COM Scan Direction
    0xDA, 0x12,  // COM Pins
    0x81, 0xCF,  // Contrast
    0xD9, 0xF1,  // Pre-charge
    0xDB, 0x40,  // VCOM
    0x20, 0x10,  // Memory Mode: Page
    0xA6,        // Normal Display
    0xAF         // Display ON
};

int8_t ssd1315_display_init(ssd1315_display_t* disp, uint8_t addr, uint8_t* buffer){
    if(buffer == NULL) return -1;
    if(disp == NULL) return -2;

    disp->I2C_device.addr = addr;
    disp->I2C_device.dataptr = ssd1315_init_buffer;
    disp->I2C_device.data_size = 23;

    if(!(I2C1->CR1 & I2C_CR1_PE)){
        I2C_init(I2C_CLK_FREQ_HZ);
    }
    I2C_sent(&(disp->I2C_device));

    disp->I2C_device.dataptr = buffer;
    disp->I2C_device.data_size = 1024;
    return 0;
}

 