#include "joystick.h"
#include <stdint.h>
void joystick_init(){
    PA_DDR &= ~(1 << 1); //key0
    PA_CR1 |= 1 << 1;
    PA_CR2 &= ~(1 << 1);

    PA_DDR &= ~(1 << 2); //key1
    PA_CR1 |= 1 << 2;
    PA_CR2 &= ~(1 << 2);

    ADC_CR1 |= 1 << 0; //joy
    ADC_CSR &= ~4;
    ADC_CSR |= 3;
}

uint8_t joy = 0;
uint16_t x = 0;
uint16_t y = 0;

uint8_t joystick_state(){
    joy = 0;

    if (!(PA_IDR & (1 << 1))) { //key0
        joy |= (1 << 0);
    } else {
        joy &= ~(1 << 0);
    }

    if (!(PA_IDR & (1 << 2))) { //key1
        joy |= (1 << 1);
    } else {
        joy &= ~(1 << 1);
    }

    ADC_CSR &= ~(1 << 7); //ch3
    ADC_CR1 |= 1;
    while (!(ADC_CSR & (1 << 7)));
    x = ADC_DRH;
    x <<= 2;
    x |= ADC_DRL;
    ADC_CSR &= ~3;
    ADC_CSR |= 4;

    ADC_CSR &= ~(1 << 7); //ch4
    ADC_CR1 |= 1;
    while (!(ADC_CSR & (1 << 7)));
    y = ADC_DRH;
    y <<= 2;
    y |= ADC_DRL;
    ADC_CSR &= ~4;
    ADC_CSR |= 3;


    if (y > 800) { // right
        joy |= (1 << 5);
    } else {
        joy &= ~(1 << 5);
    }

    if (y < 200) { // left
        joy |= (1 << 4);
    } else {
        joy &= ~(1 << 4);
    }

    if (x > 800) { //up
        joy |= (1 << 2);
    } else {
        joy &= ~(1 << 2);
    }

    if (x < 200) { //down
        joy |= (1 << 3);
    } else {
        joy &= ~(1 << 3);
    }

    return joy;
}
