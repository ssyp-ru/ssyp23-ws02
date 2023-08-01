#include <stdint.h>
#ifndef __JOYSTIC_H__
#define __JOYSTIC_H__

#define PA_DDR (*(volatile uint8_t*)0x5002) // key
#define PA_CR1 (*(volatile uint8_t*)0x5003)
#define PA_CR2 (*(volatile uint8_t*)0x5004)
#define PA_IDR (*(volatile uint8_t*)0x5001)
#define PA_ODR (*(volatile uint8_t*)0x5000)

#define ADC_CSR (*(volatile uint8_t*)0x5400) // joy
#define ADC_CR1 (*(volatile uint8_t*)0x5401)
#define ADC_CR2 (*(volatile uint8_t*)0x5402)
#define ADC_DRH (*(volatile uint8_t*)0x5404)
#define ADC_DRL (*(volatile uint8_t*)0x5405)

void joystick_init();

uint8_t joystick_state();

#endif
