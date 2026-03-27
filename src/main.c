#include <dma.h>
#include <i2c.h>
#include <oled_ssd1315.h>
#include <fonts.h>
#include <tengine.h>
int main(){
    __enable_irq();
    ssd1315_display_t display;
    tengine_t text;
    tengine_init(&text, font_8x8);
    for(int i = 0; i < 1024; i++){
        display.data_buffer[i] = 0;
    }
    ssd1315_display_init(&display, 0x3C);
    ssd1315_display_update(&display);
    for(volatile int i = 0; i < 10000; i++){ __NOP();}
    char* str = "SANCTUM FUCKS YOU BITCH";
    tengine_print(&text, display.data_buffer, str, 23);
    while(1){
        ssd1315_display_update(&display);
    };
    
    return 0;
}