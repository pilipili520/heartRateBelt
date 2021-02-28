#ifndef _TIMER2_H
#define _TIMER2_H


#include <stm32f10x.h>

void timer2_configer(int psc,int arr);
void TIM2_IRQHandler(void);
#endif