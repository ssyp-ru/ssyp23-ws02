#ifndef __timer_H__

#define TIM4_SR (*(volatile uint8_t*)0x5342)
#define TIM4_IER (*(volatile uint8_t*)0x5341)
#define TIM4_CR1 (*(volatile uint8_t*)0x5340)
#define TIM4_EGR (*(volatile uint8_t*)0x5343)
#define TIM4_CNTR (*(volatile uint8_t*)0x5344)
#define TIM4_PSCR (*(volatile uint8_t*)0x5345)
#define TIM4_ARR (*(volatile uint8_t*)0x5346)

#include <stdint.h>
#define __timer_H__

void timer_init();
void dl()__interrupt(23);
void delay(long int time);
long int get_time();

#endif
