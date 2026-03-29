#include <dma.h>
#include <i2c.h>
#include <oled_ssd1315.h>
#include <uart.h>
#include <tengine.h>
int main(){
    __enable_irq();
    UARTInit(0);
    ssd1315_display_t display;
    tengine_t text;
    tengine_init(&text, (const uint8_t*)font_8x8);
    for(int i = 0; i < 1024; i++){
        display.data_buffer[i] = 0;
    }
    ssd1315_display_init(&display, 0x3C);
    ssd1315_display_update(&display);

    while(1){
        if(data_is_readable)
        {
            tengine_print(&text, display.data_buffer, read_data_buffer, RX_size);
            data_is_readable = 0;
            for(volatile int i = 0; i < 10000; i++){__NOP();}
        }
        ssd1315_display_update(&display);
    };
    
    return 0;
}