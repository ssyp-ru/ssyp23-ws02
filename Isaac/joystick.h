#ifndef JOYSTICK_H_INCLUDED
#define JOYSTICK_H_INCLUDED

#include "memory.h"
#define X_CH 3
#define Y_CH 4

extern int16_t stick_deadzone;

void joystick_init();

void ADC_reset_channel();

void ADC_set_channel(uint8_t channel);

void ADC_reset_channel();

void ADC_set_channel(uint8_t channel);

uint16_t ADC_get_input();

uint16_t ADC_get_input_from_channel(uint8_t channel);

int16_t ADC_format(uint16_t coord, int8_t mult);

int16_t ADC_get_vec();

int16_t ADC_get_vec_from_channel(uint8_t channel, int8_t mult);

#endif // JOYSTICK_H_INCLUDED
