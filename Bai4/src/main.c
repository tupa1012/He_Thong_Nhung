
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
    

    // GPIOA + GPIOC
    RCC->APB2ENR |= (1 << 2);
    RCC->APB2ENR |= (1 << 4);

    // PA0 _input
    GPIOA->CRL &= ~(0xF << 0);
    GPIOA->CRL |=  (0x8 << 0);
    GPIOA->ODR |= (1 << 0);

 
    GPIOC->CRH &= ~(0xF << 20);
    GPIOC->CRH |=  (0x3 << 20);


    GPIOC->BSRR = (1 << 13);

    uint8_t old_button = 1;

    while (1)
    {
        uint8_t button = (GPIOA->IDR & (1 << 0)) ? 1 : 0;

        if (old_button == 1 && button == 0)
        {
            delay_ms(20);

            // Vẫn đang nhấn
            if ((GPIOA->IDR & (1 << 0)) == 0)
            {
                GPIOC->ODR ^= (1 << 13);

                delay_ms(100);
            }
        }

        old_button = 1;
    }
}
