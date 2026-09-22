#include "uart.h"

static volatile char command[32];
static volatile uint8_t index = 0;
static volatile uint8_t ready = 0;

void UART_Init(void)
{
    /* Clock GPIOA + USART1 */
    RCC->APB2ENR |= (1 << 2) | (1 << 14);

    /* PA9 = USART1_TX
       Alternate Function Push-Pull, 50 MHz */
    GPIOA->CRH &= ~(0xF << 4);
    GPIOA->CRH |=  (0xB << 4);

    /* PA10 = USART1_RX
       Input Floating */
    GPIOA->CRH &= ~(0xF << 8);
    GPIOA->CRH |=  (0x4 << 8);

    /*
       HSI = 8 MHz
       Baud = 115200
       BRR = 0x45
    */
    USART1->BRR = 0x45;

    /*
       UE    = bit 13 -> USART Enable
       RXNEIE= bit 5  -> RX interrupt Enable
       TE    = bit 3  -> Transmitter Enable
       RE    = bit 2  -> Receiver Enable
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

void USART1_IRQHandler(void)
{
    char c;

    /* RXNE */
    if (USART1->SR & (1 << 5))
    {
        c = USART1->DR;

        /* Bỏ qua Enter */
        if (c == '\r' || c == '\n')
            return;

        /* ! = kết thúc lệnh */
        if (c == '!')
        {
            command[index] = '\0';
            ready = 1;
            index = 0;
        }
        else
        {
            if (index < 31)
            {
                command[index++] = c;
            }
        }
    }
}

uint8_t UART_CommandReady(void)
{
    return ready;
}

void UART_GetCommand(char *cmd)
{
    uint8_t i;

    for (i = 0; i < 32; i++)
    {
        cmd[i] = command[i];

        if (command[i] == '\0')
            break;
    }

    ready = 0;
}
