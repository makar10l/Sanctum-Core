#include <i2c.h>
#include <config.h>
#include <PinInitializer.h>
#include <uart.h>

static volatile uint8_t g_address = BASE_I2C_DEVICE_ADDR;
static volatile uint16_t g_dataidx = 0;
static volatile uint8_t* g_dataptr = NULL;
static volatile uint16_t g_data_size = 0;
static volatile uint8_t g_i2c_busy_flag = 0;

int8_t I2C_init(uint16_t clk_freq_hz){
    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
    NVIC_EnableIRQ(I2C1_EV_IRQn);
    NVIC_EnableIRQ(I2C1_ER_IRQn);
    NVIC_SetPriority(I2C1_ER_IRQn, 0);
    NVIC_SetPriority(I2C1_EV_IRQn, 1);
    PinInit(GPIOB, 6, 0b1111);
    PinInit(GPIOB, 7, 0b1111);

    I2C1->CR2 = APB1_FREQ_MHZ;
    I2C1->CR2 |= I2C_CR2_ITEVTEN | I2C_CR2_ITBUFEN | I2C_CR2_ITERREN;
    I2C1->CCR = (APB1_FREQ_MHZ * 1000000) / (2 * clk_freq_hz);
    I2C1->TRISE = (APB1_FREQ_MHZ * 1000 / 1000) + 1;
    I2C1->OAR1 = BASE_I2C_OAR; 
    I2C1->CR1 |= I2C_CR1_PE;
    return 0;
}

int8_t I2C_sent(i2c_device_t* device){
    if(I2C1->SR2 & I2C_SR2_BUSY) return -1;
    if(g_i2c_busy_flag) return -2;
    if(device == NULL) return -3;

    g_i2c_busy_flag = 1;
    g_data_size = device->data_size;
    g_dataptr = device->dataptr;
    g_address = device->addr;
    g_dataidx = 0;

    I2C1_START();  
    return 0;  
}

void I2C1_EV_IRQHandler(){
    if(I2C1->SR1 & I2C_SR1_SB){
        I2C1->DR = (g_address << 1) | 0; 
    }
    if(I2C1->SR1 & I2C_SR1_ADDR){
        (void)I2C1->SR2; 
        I2C1->DR = g_dataptr[g_dataidx];
        g_dataidx++;
    }
    if(I2C1->SR1 & I2C_SR1_TXE){
        if(g_dataidx >= g_data_size){
            I2C1_STOP();
            g_i2c_busy_flag = 0;
            return;
        }
        I2C1->DR = g_dataptr[g_dataidx];
        g_dataidx++;
    }
}

void I2C1_ER_IRQHandler(){
    if(I2C1->SR1 & I2C_SR1_AF){
        I2C1->SR1 &= ~I2C_SR1_AF;
        g_i2c_busy_flag = 0;
        I2C1_STOP();
    }
}