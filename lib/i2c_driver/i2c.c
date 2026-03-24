#include <i2c.h>
#include <config.h>
#include <PinInitializer.h>
#include <uart.h>
#include <PWM_driver.h>
UARTPackage _msg = {
    .chars = "ACK",
    .size = 3,
};
uint8_t I2C_init(uint16_t clk_freq_hz){
    RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;
    PinInit(GPIOB, 10, 0b1111);
    PinInit(GPIOB, 11, 0b1111);
    I2C2->CR2 = APB1_FREQ_MHZ;
    I2C2->CCR = (APB1_FREQ_MHZ * 1000000) / (2 * clk_freq_hz);
    I2C2->TRISE = (APB1_FREQ_MHZ * 1000 / 1000) + 1;
    I2C2->CR1 |= I2C_CR1_PE;
    return 0;
}
//rewrite
// void I2C_SentAddress(uint8_t addr_7bit)
// {
//     //while(I2C2->SR2 & I2C_SR2_BUSY);           // ждем шину
//     I2C2->CR1 |= I2C_CR1_START;                // START
//     //while(!(I2C2->SR1 & I2C_SR1_SB));          // ждем START
//     I2C2->DR = (addr_7bit << 1) | 0;           // адрес + запись
//     //while(!(I2C2->SR1 & I2C_SR1_ADDR));       // ждем ACK
//     UartSend(&_msg);
//     SetLampBrightness(25);
//     (void)I2C2->SR1; (void)I2C2->SR2;          // сброс ADDR
// }
