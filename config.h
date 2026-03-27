#define CLOCKING 8 * 1000000
#define BAUDRATE 9600
#define PWM_TIM_PSC (CLOCKING / (1000 * (99 + 1))) - 1
#define APB1_FREQ_MHZ 8

#define BASE_I2C_OAR 0x00
#define BASE_I2C_DEVICE_ADDR 0x00

#define NULL ((void*)0)

#define I2C_CLK_FREQ_HZ (int)100000 
