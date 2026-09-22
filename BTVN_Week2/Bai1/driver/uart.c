#include "uart.h"

static volatile char rx_buffer[64];
static volatile uint8_t index = 0;
static volatile uint8_t ready = 0;

void UART_Init(void)
{
    /* Clock GPIOA + USART1 */
    RCC->APB2ENR |= (1 << 2) | (1 << 14);

    /*
       PA9 = USART1_TX
       Alternate Function Push-Pull, 50 MHz
    */
    GPIOA->CRH &= ~(0xF << 4);
    GPIOA->CRH |=  (0xB << 4);

    /*
       PA10 = USART1_RX
       Input Floating
    */
    GPIOA->CRH &= ~(0xF << 8);
    GPIOA->CRH |=  (0x4 << 8);

    /*
       HSI = 8 MHz
       Baud = 115200
    */
    USART1->BRR = 0x45;

    /*
       UE    = 1  USART Enable
       RXNEIE= 1  RX interrupt enable
       TE    = 1  Transmitter enable
       RE    = 1  Receiver enable
    */
    USART1->CR1 = (1 << 13)
                | (1 << 5)
                | (1 << 3)
                | (1 << 2);

    /* Enable USART1 interrupt */
    NVIC_EnableIRQ(USART1_IRQn);
}

void UART_SendChar(char c)
{
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

/* USART1 Interrupt */
void USART1_IRQHandler(void)
{
    char c;

    /* RXNE */
    if (USART1->SR & (1 << 5))
    {
        c = USART1->DR;

        /* ! = ký tự kết thúc */
        if (c == '!')
        {
            rx_buffer[index] = '\0';
            ready = 1;
            index = 0;
        }
        else
        {
            /* Bỏ qua \r và \n */
            if (c != '\r' && c != '\n')
            {
                if (index < 63)
                {
                    rx_buffer[index++] = c;
                }
            }
        }
    }
}

uint8_t UART_CommandReady(void)
{
    return ready;
}

void UART_GetBuffer(char *buf)
{
    uint8_t i;

    for (i = 0; i < 64; i++)
    {
        buf[i] = rx_buffer[i];

        if (rx_buffer[i] == '\0')
            break;
    }

    ready = 0;
}
