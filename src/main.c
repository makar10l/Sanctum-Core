#include <uart.h>
#include <dma.h>
#include <i2c.h>
#include <oled_ssd1315.h>
int main(){
    __enable_irq();
    uint8_t buffer[1024];
    ssd1315_display_t display;
    ssd1315_display_init(&display, 0x3C, &buffer);
    while(1){
        ssd1315_display_off(&display);
        for(volatile int i = 0; i < 500000; i++);
        ssd1315_display_on(&display);
        for(volatile int i = 0; i < 500000; i++);
    }
    return 0;
}  