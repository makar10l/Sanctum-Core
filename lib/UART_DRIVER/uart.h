#ifndef UART_H
#define UART_H
#include <stm32f1xx.h>
#include <RingBuffer.h>
typedef struct{
    char* chars;
    int size;
} UARTPackage
;
int UARTInit(uint8_t remapping);
int UartSend(UARTPackage* msg);
extern char read_data_buffer[256];
extern volatile uint8_t RX_size;
extern volatile uint8_t data_is_readable;
extern RingBuffer UART_BUFFER;
#endif