#include <stm32f1xx.h>
#include <PinInitializer_0.1v.h>
#include <PWM_driver.h>
int main(){
    INIT_LED();
    SetLampBrightness(25);

    while(1){}
    return 0;
}  