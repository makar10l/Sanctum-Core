#include <PWM_driver.h>
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
//uint8_t cmds[] = {0x00, 0xAF};
uint8_t white_data[1025];
UARTPackage msg = {
    .chars = cmds,
    .size = 23,
};
UARTPackage data = {
    .chars = white_data,
    .size = 1025,
};
int main(){
    NVIC_EnableIRQ(I2C1_EV_IRQn);
    white_data[0] = 0x40;
    // Залить первую половину белым
for(int i = 1; i < 513; i++) {
    white_data[i] = 0xFF;
}
// Вторую половину чёрным
for(int i = 513; i < 1025; i++) {
    white_data[i] = 0x00;
}
    __enable_irq();
    INIT_LED();
    //BufferInit();
    I2C_init(100000); 
    I2C_sent(0x3C, msg);

   // I2C_sent(0x3C, msg);
    //UARTInit(1);
    //DMAInit();
    SetLampBrightness(0);
    while(1){
        if(I2C_sent(0x3C, data) == -2){
        for(volatile int i = 0; i < 10000; i++);
        }
        __WFI();
    }
    return 0;
}  