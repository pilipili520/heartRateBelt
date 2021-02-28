#ifndef _SYSTICK_H
#define _SYSTICK_H

#include <stm32f10x.h>
#include <stdint.h>

void delay_us(int32_t nus);
void delay_ms(int16_t nms);

#endif