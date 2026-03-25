#ifndef I2C
#define I2C
#define I2C1_STOP() I2C1->CR1 |= I2C_CR1_STOP
#define I2C1_START() I2C1->CR1 |= I2C_CR1_START
#include <stm32f1xx.h>
#include <uart.h>
    typedef struct   
    {
        uint8_t addr;
        uint8_t* dataptr;
        uint16_t data_size;
    } i2c_device_t;
    
    int8_t I2C_init(uint16_t clk_freq_hz); 
    int8_t I2C_sent(i2c_device_t* device);

#endif