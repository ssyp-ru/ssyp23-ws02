#ifndef LCD_H_INCLUDED
#define LCD_H_INCLUDED

#include <stdint.h>

#define DATA_PORT       (volatile uint8_t*)0x500A
#define CONTROL_PORT    (volatile uint8_t*)0x500A

#define ODR_OFFSET      0
#define IDR_OFFSET      1
#define DDR_OFFSET      2
#define CR1_OFFSET      3
#define CR2_OFFSET      4

#define RS              7
#define RW              6
#define E               5
#define DATA            1

#define TIM4_CR1 (*(volatile uint8_t*)0x5340)
#define TIM4_IER (*(volatile uint8_t*)0x5341)
#define TIM4_SR (*(volatile uint8_t*)0x5342)
#define TIM4_EGR (*(volatile uint8_t*)0x5343)
#define TIM4_CNTR (*(volatile uint8_t*)0x5344)
#define TIM4_PSCR (*(volatile uint8_t*)0x5345)
#define TIM4_ARR (*(volatile uint8_t*)0x5346)

#define OPM             3
#define CEN             0
#define UIF             0

#define COMMAND         0

#define CLEAR           0x01
#define HOME            0x02

void delay(uint16_t delay);

void LCD_send_byte(uint8_t data, uint8_t mode);

void LCD_init();

void LCD_set_pos(uint8_t x, uint8_t y);

void LCD_clear();

#endif // LCD_H_INCLUDED
