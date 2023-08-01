#include "joystick.h"
#include "LCD.h"
#include <stdint.h>

void joystick_init() {
    /*PB_DDR |= (1 << 5);
    PB_CR1 |= (1 << 5);
    PB_CR2 |= (1 << 5);
    PB_IDR |= (1 << 5);*/

    PA_DDR &= ~(1 << 1);
    PA_CR1 |= (1 << 1);
    PA_CR2 &= ~(1 << 1);

    PA_DDR &= ~(1 << 2);
    PA_CR1 |= (1 << 2);
    PA_CR2 &= ~(1 << 2);

    ADC_CR1 |= 1;
}

uint8_t joystick;

uint8_t joystick_state() {
    // button
    if (!(PA_IDR & (1 << 1))) {
        joystick |= 1;
    } else {
        joystick &= ~1;
    }
    if (!(PA_IDR & (1 << 2))) {
        joystick |= (1 << 1);
    } else {
        joystick &= ~(1 << 1);
    }
    // stick
    /*ADC_CSR &= ~4;
    ADC_CSR &= ~(1 << 7);
    ADC_CSR |= 3;
    ADC_CR1 |= 1;
    while (!(ADC_CSR & (1 << 7)));
    x = ADC_DRH;
    x <<= 2;
    x |= ADC_DRL;
    if (x > 800) {
        joystick |= (1 << 4);
    } else {
        joystick &= ~(1 << 4);
    }
    if (x < 300) {
        joystick |= (1 << 5);
    } else {
        joystick &= ~(1 << 5);
    }
    ADC_CSR &= ~3;
    ADC_CSR &= ~(1 << 7);
    ADC_CSR |= 4;
    ADC_CR1 |= 1;
    while (!(ADC_CSR & (1 << 7)));
    y |= ADC_DRH;
    y <<= 2;
    y |= ADC_DRL;
    if (y > 800) {
        joystick |= (1 << 2);
    } else {
        joystick &= ~(1 << 2);
    }
    if (y < 300) {
        joystick |= (1 << 3);
    } else {
        joystick &= ~(1 << 3);
    }*/
    return joystick;
}
