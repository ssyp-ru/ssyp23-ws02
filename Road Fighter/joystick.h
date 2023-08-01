#ifndef __joystick_H__

#include <stdint.h>
#define __joystick_H__

#define ADC_CSR (*(volatile uint8_t*)0x5400)
#define ADC_CR1 (*(volatile uint8_t*)0x5401)
#define ADC_CR2 (*(volatile uint8_t*)0x5402)
#define ADC_DRH (*(volatile uint8_t*)0x5404)
#define ADC_DRL (*(volatile uint8_t*)0x5405)

#define PA_ODR (*(volatile uint8_t*)0x5000)
#define PA_IDR (*(volatile uint8_t*)0x5001)
#define PA_DDR (*(volatile uint8_t*)0x5002)
#define PA_CR1 (*(volatile uint8_t*)0x5003)
#define PA_CR2 (*(volatile uint8_t*)0x5004)
void joystick_init(void);
uint8_t joystick_state();

#endif // __joystick_H__
