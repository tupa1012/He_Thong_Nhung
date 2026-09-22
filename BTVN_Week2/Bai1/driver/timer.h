#ifndef TIMER_H
#define TIMER_H

#include "stm32f10x.h"

void Timer_PWM_Init(void);
void PWM_SetDuty(uint8_t percent);
void PWM_On(void);
void PWM_Off(void);
uint8_t PWM_GetDuty(void);
uint8_t PWM_GetState(void);

#endif
