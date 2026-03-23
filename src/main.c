#include <stm32f1xx.h>
#include <PinInitializer.h>
#include <PWM_driver.h>
#include <config.h>
#include <uart.h>
#include <dma.h>
UARTPackage msg = {
    .chars = "25",
    .size = 2,
};
int main(){
    __enable_irq();
    INIT_LED();
    BufferInit();
    UARTInit(1);
    DMAInit();
    SetLampBrightness(100);
    while(1){
        UartSend(&msg);
        for(volatile int i = 0; i < 10000; i++);
    }
    return 0;
}  