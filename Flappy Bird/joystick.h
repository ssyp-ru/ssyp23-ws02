#ifndef JOYSTICK_H_INCLUDED
#define JOYSTICK_H_INCLUDED

#include <stdint.h>

#define PB_ODR (*(volatile char*)0x5005)
#define PB_IDR (*(volatile char*)0x5006)
#define PB_DDR (*(volatile char*)0x5007)
#define PB_CR1 (*(volatile char*)0x5008)
#define PB_CR2 (*(volatile char*)0x5009)
#define TIM2_ARRH (*(volatile char*)0x530D)
#define TIM2_ARRL (*(volatile char*)0x530E)
#define TIM2_CCR1H (*(volatile char*)0x530F)
#define TIM2_CNTRL (*(volatile char*)0x530B)
#define TIM2_CNTRH (*(volatile char*)0x530A)
#define TIM2_CCR1L (*(volatile char*)0x5310)
#define TIM2_PSCR (*(volatile char*)0x530E)
#define TIM2_CCMR1 (*(volatile char*)0x5307)
#define TIM2_CCER1 (*(volatile char*)0x530A)
#define TIM2_IER (*(volatile char*)0x5303)
#define TIM2_CR1 (*(volatile char*)0x5300)
#define TIM2_SR1 (*(volatile char*)0x5304)
#define ADC_CSR (*(volatile char*)0x5400)
#define ADC_CR1 (*(volatile char*)0x5401)
#define ADC_DRL (*(volatile char*)0x5405)
#define ADC_DRH (*(volatile char*)0x5404)
#define PC_ODR (*(volatile char*)0x500A)
#define PC_IDR (*(volatile char*)0x500B)
#define PC_DDR (*(volatile char*)0x500C)
#define PC_CR1 (*(volatile char*)0x500D)
#define PC_CR2 (*(volatile char*)0x500E)
//#define SPI_CR1 (*(volatile char*)0x5200)
//#define SPI_CR2 (*(volatile char*)0x5201)
//#define SPI_ICR (*(volatile char*)0x5202)
//#define SPI_SR (*(volatile char*)0x5203)
//#define SPI_DR (*(volatile char*)0x5204)
#define PA_ODR (*(volatile char*)0x5000)
#define PA_IDR (*(volatile char*)0x5001)
#define PA_DDR (*(volatile char*)0x5002)
#define PA_CR1 (*(volatile char*)0x5003)
#define PA_CR2 (*(volatile char*)0x5004)

void joystick_init();
uint8_t joystick_state();

#endif // JOYSTICK_H_INCLUDED
