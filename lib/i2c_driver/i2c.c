#include <i2c.h>
#include <config.h>
#include <PinInitializer.h>
#include <uart.h>
#include <PWM_driver.h>
uint8_t i2c_device_address;
uint16_t dataidx = 0;
uint8_t* dataptr;
uint8_t data_size = 0;
uint8_t BUSY_BUS = 0;
uint8_t I2C_init(uint16_t clk_freq_hz){
    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
    PinInit(GPIOB, 6, 0b1111);
    PinInit(GPIOB, 7, 0b1111);
    I2C1->CR2 = APB1_FREQ_MHZ;
    I2C1->CR2 |= I2C_CR2_ITEVTEN | I2C_CR2_ITBUFEN;
    I2C1->CCR = (APB1_FREQ_MHZ * 1000000) / (2 * clk_freq_hz);
    I2C1->TRISE = (APB1_FREQ_MHZ * 1000 / 1000) + 1;
    I2C1->OAR1 = 0x00; 
    I2C1->CR1 |= I2C_CR1_PE;
    return 0;
}

int8_t I2C_sent(uint8_t addr, UARTPackage data){
    if(I2C1->SR2 & I2C_SR2_BUSY){
        return -1;
    }
    if(BUSY_BUS) return -2;
    data_size = data.size;
    dataptr = (uint8_t*)data.chars;
    i2c_device_address = addr;
    dataidx = 0;
    BUSY_BUS = 1;
    I2C1->CR1 |= I2C_CR1_START;  
    return 0;  
}

void I2C1_EV_IRQHandler(){
    if(I2C1->SR1 & I2C_SR1_SB){
        I2C1->DR = (i2c_device_address << 1) | 0; 
    }
    if(I2C1->SR1 & I2C_SR1_ADDR){
        (void)I2C1->SR2; 
        I2C1->DR = dataptr[dataidx];
        dataidx++;
    }
    if(I2C1->SR1 & I2C_SR1_TXE){
        if(dataidx >= data_size){
            I2C1->CR1 |= I2C_CR1_STOP;
            BUSY_BUS = 0;
            return;
        }
        I2C1->DR = dataptr[dataidx];
        dataidx++;
    }
}