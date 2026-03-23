#include <PWM_driver.h>
#include <stm32f1xx.h>
#include <config.h>
#include <PinInitializer.h>
void INIT_LED(){
    PinInit(LED_PIN, 0b1011); // initializing pin 
    //clocking for TIM1
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    TIM2->PSC = PWM_TIM_PSC;
    TIM2->ARR = 99;
    //(0b110 is bitmask for PWM1 mode)
    TIM2->CCMR1 |= (0b110 << 4) | TIM_CCMR1_OC1PE;// <- it is just important
    TIM2->CCER |= TIM_CCER_CC1E; // enabling input for 1st channel
    TIM2->CR1 |= TIM_CR1_CEN;
    TIM2->CCR1 = 100;
}

int SetLampBrightness(uint16_t brightness){
    if(brightness > 100) return 1;
    TIM2->CCR1 = (uint16_t)(100 - brightness);
    return 0;
}