#define CLOCKING 8 * 1000000
#define BAUDRATE 9600
#define LED_PIN GPIOA, 0
#define PWM_TIM_PSC (CLOCKING / (1000 * (99 + 1))) - 1
#define APB1_FREQ_MHZ 8
