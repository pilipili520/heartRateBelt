#ifndef _TIMER_H
#define _TIMER_H


#include <stm32f10x.h>
static int8_t timer_state = 0;
void TIM2_Configer(int16_t arr, int16_t psc);
void TIM_IRQHandler(void);

#endif