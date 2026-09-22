#include "stm32f10x.h"
#include "adc.h"
#include "uart.h"

void delay_1s(void)
{
    /* HSI = 8 MHz */
    SysTick->LOAD = 8000000 - 1;
    SysTick->VAL = 0;
    SysTick->CTRL = 5;

    while (!(SysTick->CTRL & (1 << 16)));

    SysTick->CTRL = 0;
}

int main(void)
{
    uint16_t adc;
    uint16_t voltage;

    ADC_Init();
    UART_Init();

    UART_SendString("ADC START\r\n");

    while (1)
    {
        adc = ADC_Read();
        voltage = (adc * 3300) / 4095;

        UART_SendString("ADC = ");
        UART_SendNumber(adc);

        UART_SendString(" | Voltage = ");
        UART_SendNumber(voltage);

        UART_SendString(" mV\r\n");

        delay_1s();
    }
}
