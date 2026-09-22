#include "timer.h"

static uint8_t duty = 50;
static uint8_t state = 0;

void Timer_PWM_Init(void)
{
    /* Bật clock GPIOA */
    RCC->APB2ENR |= (1 << 2);

    /* Bật clock TIM2 */
    RCC->APB1ENR |= (1 << 0);

    /* PA0 = TIM2_CH1
       Alternate Function Push-Pull, 50 MHz */
    GPIOA->CRL &= ~(0xF << 0);
    GPIOA->CRL |= (0xB << 0);

    /*
       HSI = 8 MHz

       8 MHz / (7 + 1) = 1 MHz
       1 MHz / (999 + 1) = 1 kHz
    */
    TIM2->PSC = 7;
    TIM2->ARR = 999;

    /* PWM Mode 1 - CH1 */
    TIM2->CCMR1 &= ~(0x7 << 4);
    TIM2->CCMR1 |=  (0x6 << 4);

    /* Preload CCR1 */
    TIM2->CCMR1 |= (1 << 3);

    /* Duty mặc định 50% */
    TIM2->CCR1 = 500;

    /* Enable TIM2 CH1 */
    TIM2->CCER |= (1 << 0);

    /* Update registers */
    TIM2->EGR |= (1 << 0);

    /* Enable Timer */
    TIM2->CR1 |= (1 << 0);

    /* Ban đầu OFF */
    TIM2->CCER &= ~(1 << 0);
}

void PWM_SetDuty(uint8_t percent)
{
    if (percent > 100)
        percent = 100;

    duty = percent;

    TIM2->CCR1 = ((TIM2->ARR + 1) * percent) / 100;
}

void PWM_On(void)
{
    TIM2->CCER |= (1 << 0);
    state = 1;
}

void PWM_Off(void)
{
    TIM2->CCER &= ~(1 << 0);
    state = 0;
}

uint8_t PWM_GetDuty(void)
{
    return duty;
}

uint8_t PWM_GetState(void)
{
    return state;
}
