
#include "stm32f10x.h"



void delay_ms(uint32_t ms)
{
    SysTick->LOAD = 8000 - 1;
    SysTick->VAL  = 0;

    /* Clock = processor clock
       Enable SysTick */
    SysTick->CTRL = 5;

    while (ms--)
    {
        while (!(SysTick->CTRL & (1 << 16)));
    }

    SysTick->CTRL = 0;
}


/* =========================
   MAIN
   ========================= */
int main(void)
{


    /* Enable GPIOC clock */
    RCC->APB2ENR |= (1 << 4);

    /* PC13 = Output Push-Pull, 2 MHz */
    GPIOC->CRH &= ~(0xF << 20);
    GPIOC->CRH |=  (0x3 << 20);

    while (1)
    {
        /* PC13 = 0 -> LED ON */
        GPIOC->BRR = (1 << 13);
        delay_ms(500);

        /* PC13 = 1 -> LED OFF */
        GPIOC->BSRR = (1 << 13);
        delay_ms(500);
    }
}


