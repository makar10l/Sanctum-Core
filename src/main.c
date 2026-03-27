#include <dma.h>
#include <i2c.h>
#include <oled_ssd1315.h>

int main(){
    __enable_irq();
    
    ssd1315_display_t display;
    
    // Белый экран
   for(int i = 0; i < 1024; i++){
        display.data_buffer[i] = 0;
   }
   ssd1315_display_init(&display, 0x3C);
    ssd1315_display_update(&display);
    while(1){
        ssd1315_display_update(&display);  
        for(int i = 0; i < 1024; i++) display.data_buffer[i] = 0;
        for(volatile int i = 0; i < 1000000; i++);
        ssd1315_display_update(&display); 
         for(int i = 0; i < 1024; i++) display.data_buffer[i] = 0xFF;
        for(volatile int i = 0; i < 1000000; i++);
    };
    
    return 0;
}
