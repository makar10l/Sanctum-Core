#include <stm32f1xx.h>
#include <PinInitializer.h>
#include <PWM_driver.h>
#include <config.h>
int main(){
    INIT_LED();
    SetLampBrightness(25);
    while(1){__WFI();}
    return 0;
}  