#include "timer.h"

void Timer_PWM_Init(void)
{
    /* Bật clock GPIOA + TIM2 */
    RCC->APB2ENR |= (1 << 2);
    RCC->APB1ENR |= (1 << 0);

    /*
       PA0 -> TIM2_CH1
       PA1 -> TIM2_CH2
       PA2 -> TIM2_CH3
       PA3 -> TIM2_CH4

       Alternate Function Push-Pull, 50 MHz
    */
    GPIOA->CRL = 0xBBBB;

    /*
       Timer clock = 8 MHz

       PSC = 7
       => 8 MHz / (7 + 1) = 1 MHz

       ARR = 999
       => 1 MHz / (999 + 1) = 1 kHz
    */
    TIM2->PSC = 7;
    TIM2->ARR = 999;

    /*
       PWM Mode 1
       CH1
    */
    TIM2->CCMR1 &= ~(0xFF);
    TIM2->CCMR1 |= (6 << 4);
    TIM2->CCMR1 |= (1 << 3);

    /*
       PWM Mode 1
       CH2
    */
    TIM2->CCMR1 |= (6 << 12);
    TIM2->CCMR1 |= (1 << 11);

    /*
       PWM Mode 1
       CH3
    */
    TIM2->CCMR2 |= (6 << 4);
    TIM2->CCMR2 |= (1 << 3);

    /*
       PWM Mode 1
       CH4
    */
    TIM2->CCMR2 |= (6 << 12);
    TIM2->CCMR2 |= (1 << 11);

    /*
       Duty:
       CH1 = 10%
       CH2 = 30%
       CH3 = 50%
       CH4 = 70%

       ARR = 999
    */
    TIM2->CCR1 = 0;
    TIM2->CCR2 = 20;
    TIM2->CCR3 = 100;
    TIM2->CCR4 = 900;

    /* Enable 4 PWM outputs */
    TIM2->CCER |= (1 << 0);
    TIM2->CCER |= (1 << 4);
    TIM2->CCER |= (1 << 8);
    TIM2->CCER |= (1 << 12);

    /* Enable Timer */
    TIM2->CR1 |= (1 << 0);
}
