#ifndef I2C
#define I2C
#include <stm32f1xx.h>
#include <uart.h>
    uint8_t I2C_init(uint16_t clk_freq_hz); 
    int8_t I2C_send(uint16_t address, UARTPackage data);
#endif