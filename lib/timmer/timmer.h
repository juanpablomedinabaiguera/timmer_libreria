#ifndef TIM_H
#define TIM_H
#include "stm32f103xb.h"
void delay_init();
int delay_us(uint32_t us);
int delay_ms(uint32_t ms);
void timer_init();
uint32_t timer_millis();
#endif