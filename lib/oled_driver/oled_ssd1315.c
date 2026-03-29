#include <oled_ssd1315.h>
#include <config.h>
#include <i2c.h>
uint8_t data_to_sent[DISPLAY_BUFFER_SIZE + 1];
i2c_device_t virtual_display;
//contrast command 0x00 0x81 0xCF
const uint8_t ssd1315_init_buffer[] = {
    0x00, 0xAE, 0x00, 0xD5, 0x80, 0x00, 0xA8, 0x3F, 0x00, 0xD3, 0x00,
    0x00, 0x40, 0x00, 0x8D, 0x14, 0x00, 0x20, 0x00, 0x00, 0xA1, 0x00,
    0xC8, 0x00, 0xDA, 0x12, 0x00, 0x81, 0xCF, 0x00, 0xD9, 0xF1, 0x00,
    0xDB, 0x40, 0x00, 0xA4, 0x00, 0xA6, 0x00, 0x2E, 0x00, 0xAF
};
int8_t ssd1315_display_init(ssd1315_display_t* disp, uint8_t addr){
    if(disp == NULL) return -1;

    disp->I2C_device.addr = addr;
    disp->I2C_device.dataptr = (uint8_t*)ssd1315_init_buffer;
    disp->I2C_device.data_size = 43;

    if(!(I2C1->CR1 & I2C_CR1_PE)){
        I2C_init(I2C_CLK_FREQ_HZ);
    }
    I2C_sent(&(disp->I2C_device));
    return 0;
}

int8_t ssd1315_display_setpix(ssd1315_display_t* disp, uint8_t x, uint8_t y, uint8_t state){
    if(x >= 128 || y >= 64) return -1;
    if(disp == NULL) return -2;
    uint8_t* buffer = disp->data_buffer;
    uint8_t page = y / 8;
    uint16_t index = (page * 128) + x;
    uint8_t bit = y % 8;
    if(state) buffer[index] |= (1 << bit);
    if(!state) buffer[index] &= ~(1 << bit);
    return 0;
}

int8_t ssd1315_display_update(ssd1315_display_t* disp){
    data_to_sent[0] = 0x40;
    virtual_display = disp->I2C_device;
    virtual_display.data_size = DISPLAY_BUFFER_SIZE + 1;
    virtual_display.dataptr = data_to_sent;
    for(int i = 0; i < DISPLAY_BUFFER_SIZE; i++){
            data_to_sent[i + 1] = disp->data_buffer[i];
    }

    I2C_sent(&virtual_display);
    return 0;
}