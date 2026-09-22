#include "uart.h"

void UART_Init(void)
{
    /* Bật clock GPIOA + USART1 */
    RCC->APB2ENR |= (1 << 2) | (1 << 14);

    /* PA9 = Alternate Function Push-Pull, 50 MHz */
    GPIOA->CRH &= ~(0xF << 4);
    GPIOA->CRH |=  (0xB << 4);

    /* PA10 = Input Floating */
    GPIOA->CRH &= ~(0xF << 8);
    GPIOA->CRH |=  (0x4 << 8);

    /*
       HSI = 8 MHz
       Baud = 115200
    */
    USART1->BRR = 0x45;

    /* USART Enable + Transmitter Enable */
    USART1->CR1 = (1 << 13) | (1 << 3);
}

void UART_SendChar(char c)
{
    /* Chờ TXE */
    while (!(USART1->SR & (1 << 7)));

    USART1->DR = c;
}

void UART_SendString(char *s)
{
    while (*s)
    {
        UART_SendChar(*s++);
    }
}

void UART_SendNumber(uint32_t n)
{
    char buf[10];
    int i = 0;

    if (n == 0)
    {
        UART_SendChar('0');
        return;
    }

    while (n > 0)
    {
        buf[i++] = '0' + (n % 10);
        n /= 10;
    }

    while (i--)
    {
        UART_SendChar(buf[i]);
    }
}
