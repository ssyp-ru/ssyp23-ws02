#include "timer.h"

long int oo = 0;
long int millis = 0;

void timer_init()
{

    TIM4_IER = 1<<0;
    __asm__("rim");

}

void dl()__interrupt(23)
{
    oo++;
    millis++;
    TIM4_SR = 0<<0;
}

void delay(long int time)
{
    oo = 0;
    TIM4_CR1 = 1<<0;
    TIM4_PSCR = 3;
    TIM4_ARR = 250;
    while (oo < time);

}

long int get_time()
{

    return millis;

}
