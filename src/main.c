#include <uart.h>
#include <dma.h>
#include <i2c.h>
uint8_t cmds[] = {
    0x00,
    0xAE,        // Display OFF
    0x8D, 0x14,  // Internal IREF ON, 30uA
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

int main(){
    __enable_irq();
    I2C_init(100000); 
    while(1){
        __WFI();
    }
    return 0;
}  