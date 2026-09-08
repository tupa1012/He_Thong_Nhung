
#include "stm32f10x.h"



void delay_ms(uint32_t ms)
{
    SysTick->LOAD = 8000 - 1;
    SysTick->VAL  = 0;


    SysTick->CTRL = 5;

    while (ms--)
    {
        while (!(SysTick->CTRL & (1 << 16)));
    }

    SysTick->CTRL = 0;
}


int main(void)
{
   

    RCC->APB2ENR |= (1 << 2);


    GPIOA->CRL = 0x33333333;

    while (1)
    {

        for (int i = 0; i < 8; i++)
        {
            GPIOA->ODR = (1 << i);
            delay_ms(300);
        }


        for (int i = 6; i >= 0; i--)
        {
            GPIOA->ODR = (1 << i);
            delay_ms(300);
        }
    }
}


