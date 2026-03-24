#include <PWM_driver.h>
#include <uart.h>
#include <dma.h>
#include <i2c.h>
UARTPackage msg = {
    .chars = "25",
    .size = 2,
};
int main(){
    __enable_irq();
    INIT_LED();
    BufferInit();
    //I2C_init(100000);
    UARTInit(1);
    DMAInit();
    SetLampBrightness(100);
    while(1){
    }
    return 0;
}  