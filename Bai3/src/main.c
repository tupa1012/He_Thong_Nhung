
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
    uint8_t data;

  
    RCC->APB2ENR |= (1 << 2);

    GPIOA->CRL = 0x88888888;

    GPIOA->ODR |= 0x00FF;

    GPIOA->CRH = 0x33333333;


    while (1)
    {
    
        data = GPIOA->IDR & 0xFF;

        data = ~data;

        /* Chỉ lấy 8 bit */
        data &= 0xFF;

        /* Xuất sang PA8 - PA15 */
        GPIOA->ODR &= ~(0xFF << 8);
        GPIOA->ODR |= ((uint16_t)data << 8);
    }
}
        old_button = 1;
    }
}
