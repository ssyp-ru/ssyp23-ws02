#include "joystick.h"
#include "LCD.h"
#include <stdint.h>
#include "ptr.h"

display_t display;
uint8_t log_left[8] = {0, 0, 0, 0, 0, 0b11111111, 0b11111111, 0b11111111};
uint8_t log_right[8] = {0b11111111, 0b11111111, 0b11111111, 0, 0, 0, 0, 0};
uint8_t ball[4] = {0b00001111, 0b00001111, 0b00001111, 0b00001111};
uint8_t addy_l = 16;
uint8_t addbacky_l = 16;
uint8_t addy_r = 16;
uint8_t addbacky_r = 16;
uint8_t blx = 42;
uint8_t bly = 16;
uint8_t blbackx = 0;
uint8_t blbacky = 0;
int8_t cntx = 1;
int8_t cnty = 1;
uint8_t num1 = 0;
uint8_t num2 = 0;
void sprite_draw_ball(uint8_t arr[4], uint8_t x, uint8_t y){
    uint8_t Page = y / 8;
    uint8_t shift = y % 8;
    uint8_t mask =  0;
    uint8_t datapx = 0;
    for (uint8_t i = 0; i < 4; ++i){
        LCD_send(&display, SET_PAGE | Page, COMMAND); // hight
        LCD_send(&display, (SET_ADDRESS | x + i), COMMAND);
        mask = 1 << (8 - shift);
        mask = mask - 1;
        datapx = arr[i] & mask;
        datapx = datapx << shift;
        LCD_send(&display, datapx, DATA);

        LCD_send(&display, SET_PAGE | Page + 1, COMMAND); // down
        LCD_send(&display, (SET_ADDRESS | x + i), COMMAND);
        mask = 1 << shift;
        mask = mask - 1;
        mask = mask << (8 - shift);
        datapx = arr[i] & mask;
        datapx = datapx >> (8 - shift);
        LCD_send(&display, datapx, DATA);
    }
}

void sprite_draw_num(uint8_t arr[8], uint8_t x, uint8_t y){
    uint8_t Page = y / 8;
    for (uint8_t i = 0; i < 8; ++i){
        LCD_send(&display, SET_PAGE | Page, COMMAND); // hight
        LCD_send(&display, (SET_ADDRESS | x + i), COMMAND);
        LCD_send(&display, (arr[i] >> 1) | 0b10000000, DATA);
    }
}

void clear(uint8_t x, uint8_t y){
    uint8_t page = y / 8;
    for (uint8_t i = 0; i < 8; ++i){
        LCD_send(&display, SET_PAGE | page, COMMAND);
        LCD_send(&display, (SET_ADDRESS | x + i), COMMAND);
        LCD_send(&display, 0b00000000, DATA);

        LCD_send(&display, SET_PAGE | page + 1, COMMAND);
        LCD_send(&display, (SET_ADDRESS | x + i), COMMAND);
        LCD_send(&display, 0b00000000, DATA);
    }
}

void clear_ball(uint8_t x, uint8_t y){
    uint8_t page = y / 8;
    for (uint8_t i = 0; i < 4; ++i){
        LCD_send(&display, SET_PAGE | page, COMMAND);
        LCD_send(&display, (SET_ADDRESS | x + i), COMMAND);
        LCD_send(&display, 0b00000000, DATA);

        LCD_send(&display, SET_PAGE | page + 1, COMMAND);
        LCD_send(&display, (SET_ADDRESS | x + i), COMMAND);
        LCD_send(&display, 0b00000000, DATA);
    }
}


void draw_log(uint8_t joy2){
        addbacky_l =  addy_l;
        addbacky_r = addy_r;
        if(joy2 & (1 << 2)){ //down
            if (addy_l < 40){
                addy_l = addy_l + 1;
            }
        }
        if(joy2 & (1 << 3)){ //up
            if (addy_l > 8){
                addy_l = addy_l - 1;
            }
        }
        if(joy2 & (1 << 1)){
            if (addy_r > 8){
                addy_r = addy_r - 1;
            }
        }
        if(joy2 & (1 << 0)){
            if (addy_r < 40){
                addy_r = addy_r + 1;
            }
        }
        clear(0, addbacky_l);
        sprite_draw(log_left, 0, addy_l);
        clear(74, addbacky_r);
        sprite_draw(log_right, 74, addy_r);
}

void score(uint8_t num1, uint8_t num2){
	sprite_draw_num((NUM_TABLE + 8 * (num1 / 100)), 0, 0);
	sprite_draw_num((NUM_TABLE + 8 * ((num1 / 10) % 10)), 8, 0);
	sprite_draw_num((NUM_TABLE + 8 * (num1 % 10)), 16, 0);

	sprite_draw_num((NUM_TABLE + 8 * (num2 / 100)), 59, 0);
	sprite_draw_num((NUM_TABLE + 8 * ((num2 / 10) % 10)), 67, 0);
	sprite_draw_num((NUM_TABLE + 8 * (num2 % 10)), 75, 0);
}

void draw_ball(){
	uint8_t flag = 0;
    if(bly == 8 || bly == 44){
        cnty = (cnty) * (-1);
    }
    if(blx == 0){
		num2 += 1;
		score(num1, num2);
		clear_ball(blx, bly);
		blx = 42;
		bly = (((num1 + num2) * 13 - 1) % 30) + 9;
		clear(0, addy_l);
		clear(74, addy_r);
		addy_l = 16;
		addy_r = 16;
		flag = 1;
		cntx = (cntx) * (-1);
	}
	if (blx == 80){
		num1 += 1;
		score(num1, num2);
		clear_ball(blx, bly);
		blx = 42;
		bly = (((num1 + num2) * 13 - 1) % 30) + 9;
		clear(0, addy_l);
		clear(74, addy_r);
		addy_l = 16;
		addy_r = 16;
		flag = 1;
		cntx = (cntx) * (-1);
	}
    if(((blx == 8)) && ((bly - addy_l >= -4) && (bly - addy_l <= 8))){
        cntx = (cntx) * (-1);
    }
    if(((blx == 70)) && ((bly - addy_r <= 8) && (bly - addy_r >= -4))){
        cntx = (cntx) * (-1);
    }
    if(((blx >= 5) && (blx < 8)) && ((bly - addy_l == -4) || (bly - addy_l == 8))){
        cnty = (cnty) * (-1);
    }
    if(((blx > 71) && (blx <= 74)) && ((bly - addy_r == -4) || (bly - addy_r == 8))){
        cnty = (cnty) * (-1);
    }

        blbackx = blx;
        blbacky = bly;
        blx += cntx;
        bly += cnty;
        clear_ball(blbackx, blbacky);
        sprite_draw_ball(ball, blx, bly);
		if (flag == 1){
            draw_log(0);
			for (uint32_t i = 0; i < 250000; ++i);
		}
}


void main(void)
{
    uint8_t joy1 = 0;
    LCD_init(&display, DIV_2);
    joystick_init();
    for (uint8_t j = 0; j < 6; ++j){
        for (uint8_t i = 0; i < 84; ++i){
            LCD_send(&display, SET_PAGE | j, COMMAND);
            LCD_send(&display, (SET_ADDRESS | i), COMMAND);
            LCD_send(&display, 0b00000000, DATA);
        }
    }

	score(num1, num2);
	for (uint8_t i = 24; i < 59; ++i){
		LCD_send(&display, SET_PAGE | 0, COMMAND);
        LCD_send(&display, (SET_ADDRESS | i), COMMAND);
        LCD_send(&display, 0b10000000, DATA);
	}

	draw_ball();
	draw_log(0);
	for (uint32_t i = 0; i < 360000; ++i);
    while(1){
        joy1 = joystick_state();
        draw_log(joy1);
        draw_ball();
        for (uint32_t i = 0; i < 8000; ++i);
    }
}
