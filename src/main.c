#include <stm32f1xx.h>
#include "../lib/PinInitializer_0.1v.h"
int SetLampBrightness(uint16_t);
void INIT_LED();
int main(){
    INIT_LED();
    SetLampBrightness(25);
    // while(1){
    //     if(GPIOA->IDR & (1 << 8)){
    //         for(int i = 0; i < 10000; i++){__NOP();}
    //         SetLampBrightness(0);
    //         for(int i = 0; i < 100000; i++){__NOP();}
    //         SetLampBrightness(50);
    //     }
    // }
    while(1){}
    return 0;
}  

void INIT_LED(){
    PinInit(GPIOA, 10, 0b1011); // initializing pin 
    //clocking for TIM1
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
    TIM1->BDTR |= TIM_BDTR_MOE;
    TIM1->PSC = 79;
    TIM1->ARR = 99;
    //(0b110 is bitmask for PWM1 mode)
    TIM1->CCMR2 |= (0b110 << 4) | TIM_CCMR2_OC3PE;// <- it is just important
    TIM1->CCER |= TIM_CCER_CC3E; // enabling input for 1st channel
    TIM1->CR1 |= TIM_CR1_CEN;
    TIM1->CCR3 = 100;
}

int SetLampBrightness(uint16_t brightness){
    if(brightness > 100) return 1;
    TIM1->CCR3 = (uint16_t)(100 - brightness);
    return 0;
}