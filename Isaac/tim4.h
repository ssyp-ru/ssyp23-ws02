#ifndef TIM4_H_INCLUDED
#define TIM4_H_INCLUDED

extern int tms;

void TIM4_init();

void TIM4_ms_tick() __interrupt(23);

void TIM4_enable();

void TIM4_disable();

void TIM4_sleep(int ms);

#endif // TIM4_H_INCLUDED
