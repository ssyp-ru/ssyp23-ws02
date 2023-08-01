#include <stdint.h>
#include "memory.h"

uint16_t tms = 0;

void TIM4_init() {
    TIM4_PSCR = 4;
    TIM4_ARR = 125;
    TIM4_IER |= 1;
}
void TIM4_ms_tick() __interrupt(23) {
    tms++;
    TIM4_SR &= ~1;
}

void TIM4_enable() {
    tms = 0;
    TIM4_CR1 |= 1;
}

void TIM4_disable() {
    TIM4_CR1 &= ~1;
}

void TIM4_sleep(uint16_t ms) {
    tms = 0;
    TIM4_enable();
    while (tms < ms)
        ;
    TIM4_disable();
}
