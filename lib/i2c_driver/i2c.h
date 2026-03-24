#ifndef I2C
#define I2C
#include <stm32f1xx.h>
typedef struct{
    char* chars;
    int size;
} I2C_package;
    uint8_t I2C_init(uint16_t clk_freq_hz); 
    uint8_t I2C_send(uint16_t address, I2C_package pkg);
#endif