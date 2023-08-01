#include "LCD.h"

void delay(uint16_t delay){
    TIM4_PSCR = 5;
    TIM4_ARR = 22;
    TIM4_CR1 |= 1 << OPM;
    for (uint16_t i = 0; i < delay; i++){
        TIM4_CR1 |= 1 << CEN;
        while (!(TIM4_SR & (1 << UIF)));
        TIM4_SR &= ~(1 << UIF);
    }
}

inline void LCD_strobe(){
    *(CONTROL_PORT + ODR_OFFSET) ^= (1 << E);
    *(CONTROL_PORT + ODR_OFFSET) ^= (1 << E);
}

void LCD_init(){
    *(DATA_PORT + DDR_OFFSET) |= 0x0F << DATA;
    *(DATA_PORT + CR1_OFFSET) |= 0x0F << DATA;
    *(DATA_PORT + CR2_OFFSET) |= 0x0F << DATA;

    *(CONTROL_PORT + DDR_OFFSET) |= (1 << RS) | (1 << RW) | (1 << E);
    *(CONTROL_PORT + CR1_OFFSET) |= (1 << RS) | (1 << RW) | (1 << E);
    *(CONTROL_PORT + CR2_OFFSET) |= (1 << RS) | (1 << RW) | (1 << E);

    delay(80);
    *(CONTROL_PORT + ODR_OFFSET) &= ~((1 << RS) | (1 << RW) | (1 << E));
    *(DATA_PORT + ODR_OFFSET) |= 0x03 << DATA;

    LCD_strobe();
    for (uint8_t i = 0; i < 20; i++);

    LCD_strobe();
    for (uint8_t i = 0; i < 20; i++);

    LCD_strobe();
    for (uint8_t i = 0; i < 20; i++);

    LCD_send_byte(0x28, COMMAND);
    LCD_send_byte(0x0C, COMMAND);
    LCD_send_byte(0x01, COMMAND);
    delay(3);
    LCD_send_byte(0x04, COMMAND);
}

void LCD_send_byte(uint8_t data, uint8_t mode){
    if (mode == COMMAND)
        *(CONTROL_PORT + ODR_OFFSET) &= ~(1 << RS);
    else
        *(CONTROL_PORT + ODR_OFFSET) |= (1 << RS);
    *(DATA_PORT + ODR_OFFSET) &= ~(0x0F << DATA);
    *(DATA_PORT + ODR_OFFSET) |= (data >> 4) << DATA;
    LCD_strobe();
    *(DATA_PORT + ODR_OFFSET) &= ~(0x0F << DATA);
    *(DATA_PORT + ODR_OFFSET) |= (data & 0x0F) << DATA;
    LCD_strobe();
    delay(1);
}

void LCD_set_pos(uint8_t x, uint8_t y){
    uint8_t address = (0x40 * y + x) | 0x80;
    LCD_send_byte(address, COMMAND);
}

void LCD_clear(){
    LCD_send_byte(CLEAR, COMMAND);
    delay(3);
}
