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
int UartRead(char* buff);

extern RingBuffer UART_BUFFER;
#endif