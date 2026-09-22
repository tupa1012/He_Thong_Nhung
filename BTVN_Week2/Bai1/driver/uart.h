#ifndef UART_H
#define UART_H

#include "stm32f10x.h"

void UART_Init(void);
void UART_SendChar(char c);
void UART_SendString(char *s);
uint8_t UART_CommandReady(void);
void UART_GetBuffer(char *buf);

#endif
