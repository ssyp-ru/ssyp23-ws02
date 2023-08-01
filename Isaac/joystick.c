#include "joystick.h"

int16_t stick_deadzone = 0;

inline int16_t abs(int16_t x) {
    return (x > 0) ? x : -x;
}

inline int16_t max(int16_t a, int16_t b) {
    return (a > b) ? a : b;
}

void joystick_init() {
    // Stick
    ADC_CR1 |= 1;

    // Buttons
    PA_DDR &= ~(1 << 1);
    PA_CR1 |= 1 << 1;
    PA_CR2 |= 1 << 1;

    PA_DDR &= ~(1 << 2);
    PA_CR1 |= 1 << 2;
    PA_CR2 |= 1 << 2;

    // Diode
    PB_DDR |= 1 << 5;
    PB_CR1 |= 1 << 5;
    PB_CR2 |= 1 << 5;
}

void ADC_reset_channel() {
    ADC_CSR &= ~15;
}

void ADC_set_channel(uint8_t channel) {
    ADC_reset_channel();
    ADC_CSR |= channel;
}

uint16_t ADC_get_input() {
    ADC_CSR &= ~(1 << 7);
    ADC_CR1 |= 1;
    while (!(ADC_CSR & (1 << 7)));
    uint16_t res = ADC_DRH;
    res <<= 2;
    res |= ADC_DRL;
    return res;
}

uint16_t ADC_get_input_from_channel(uint8_t channel) {
    ADC_set_channel(channel);
    return ADC_get_input();
}

int16_t ADC_format(uint16_t coord, int8_t mult) {
    int16_t res = coord;
    res -= 512;
    int8_t sign = (res >= 0 ? 1 : -1);
    return mult * sign * (max(0, abs(res) - stick_deadzone));
}

int16_t ADC_get_vec() {
    return ADC_format(ADC_get_input(), 0);
}

int16_t ADC_get_vec_from_channel(uint8_t channel, int8_t mult) {
    return ADC_format(ADC_get_input_from_channel(channel), mult);
}
