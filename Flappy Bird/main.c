#include <stdint.h>
#include "joystick.h"
#include "LCD.h"
#include "ptr.h"
display_t display;

uint8_t b = 1;
uint8_t x = 42;
uint8_t y = 24;
uint8_t redan = 0;
uint8_t flag = 0;
uint8_t wall_x = 83;
uint8_t aizek = 0;
uint8_t up = 15;
uint8_t down = 32;
uint8_t cnt = 0;
uint8_t flagok = 1;
uint8_t type = 1;
uint8_t blabla = 0;
uint8_t a[8] = {0b00011000, 0b01100110, 0b01000010, 0b10001101, 0b10010011, 0b01110110, 0b0110110, 0b00010000};
uint8_t empt[8] = {0, 0, 0, 0, 0, 0, 0, 0};

void sprite_draw(uint8_t arr[8], uint8_t x, uint8_t y)
{
    uint8_t Page = y / 8;
    uint8_t shift = y % 8;
    uint8_t mask =  0;
    uint8_t datapx = 0;
    for (uint8_t i = 0; i < 8; ++i)
    {
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



void clear()
{
    for (int i = 0; i < 6; i += 1)
    {
        for (int j = 0; j < 84; j += 1)
        {
            LCD_send(&display, SET_PAGE | i, COMMAND);
            LCD_send(&display, SET_ADDRESS | j, COMMAND);
            LCD_send(&display, 0, DATA);
        }
    }
}

void main()
{
    uint8_t joy;
    LCD_init(&display, DIV_2);
    joystick_init();
    clear();
    sprite_draw((NUM_TABLE + 8 * 0), 0, 0);
    sprite_draw((NUM_TABLE + 8 * 0), 9, 0);
    sprite_draw((NUM_TABLE + 8 * 0), 18, 0);
    while(1)
    {
        y += b/2;
        if (blabla == 3) {
            b += 1;
            blabla = 0;
        } else {
            blabla += 1;
        }
        if (y > 40)
        {
            break;
        }
        else
        {
            if (flag == 0)
            {
                wall_x -= 1;
                if (wall_x < 1)
                {
                    wall_x = 83;
                    flagok = 1;
                    type += 1;
                    type %= 2;
                }
                flag = 0;
                if (x > wall_x && flagok == 1) {
                    cnt += 1;
                    flagok = 0;
                }
            }
            else
            {
                flag += 1;
            }
            joy = joystick_state();
            if ((joy & 1)&&(aizek == 0))
            {
                redan = 7;
                aizek = 1;
                b = 1;
            }
            if (!(joy & 1))
            {
                aizek = 0;
            }
            if (redan > 0)
            {
                y -= 1;
                redan -= 1;
            }
            if (y < 1)
            {
                break;
            }
        }

    // DRAW
        sprite_draw(a, x, y);
        if (type == 1) {
            up = 7;
            down = 24;
            LCD_send(&display, SET_PAGE | 0, COMMAND);
            LCD_send(&display, SET_ADDRESS | wall_x, COMMAND);
            LCD_send(&display, 255, DATA);
            for (int i = 3; i < 6; i += 1) {
                LCD_send(&display, SET_PAGE | i, COMMAND);
                LCD_send(&display, SET_ADDRESS | wall_x, COMMAND);
                LCD_send(&display, 255, DATA);
            }
        } else {
            up = 23;
            down = 40;
            for (int i = 0; i < 3; i += 1) {
                LCD_send(&display, SET_PAGE | i, COMMAND);
                LCD_send(&display, SET_ADDRESS | wall_x, COMMAND);
                LCD_send(&display, 255, DATA);
            }
            LCD_send(&display, SET_PAGE | 5, COMMAND);
            LCD_send(&display, SET_ADDRESS | wall_x, COMMAND);
            LCD_send(&display, 255, DATA);
        }
        LCD_send(&display, SET_PAGE | 84, COMMAND);
        LCD_send(&display, SET_ADDRESS | 0, COMMAND);
        LCD_send(&display, 0x00, DATA);
        for (int i = 0; i < 15000; i += 1);
        sprite_draw(empt, x, y);
        if (type == 1) {
            LCD_send(&display, SET_PAGE | 0, COMMAND);
            LCD_send(&display, SET_ADDRESS | wall_x, COMMAND);
            LCD_send(&display, 0, DATA);
            for (int i = 3; i < 6; i += 1) {
                LCD_send(&display, SET_PAGE | i, COMMAND);
                LCD_send(&display, SET_ADDRESS | wall_x, COMMAND);
                LCD_send(&display, 0, DATA);
            }
        } else {
            for (int i = 0; i < 3; i += 1) {
                LCD_send(&display, SET_PAGE | i, COMMAND);
                LCD_send(&display, SET_ADDRESS | wall_x, COMMAND);
                LCD_send(&display, 0, DATA);
            }
            LCD_send(&display, SET_PAGE | 5, COMMAND);
            LCD_send(&display, SET_ADDRESS | wall_x, COMMAND);
            LCD_send(&display, 0, DATA);
        }
        sprite_draw((NUM_TABLE + 8 * (cnt / 100)), 0, 0);
        sprite_draw((NUM_TABLE + 8 * ((cnt / 10) % 10)), 9, 0);
        sprite_draw((NUM_TABLE + 8 * (cnt % 10)), 18, 0);
    //COLOSII
        if (x + 7 >= wall_x && x <= wall_x) {
            if (y < up || y + 7 > down) {
                break;
            }
        }
    }
    clear();
    sprite_draw((CHAR_UC_TABLE  + 8 * ('g' - 'a')), 0, 0);
    sprite_draw((CHAR_UC_TABLE  + 8 * ('a' - 'a')), 9, 0);
    sprite_draw((CHAR_UC_TABLE  + 8 * ('m' - 'a')), 18, 0);
    sprite_draw((CHAR_UC_TABLE  + 8 * ('e' - 'a')), 27, 0);
    sprite_draw((CHAR_UC_TABLE  + 8 * ('o' - 'a')), 45, 0);
    sprite_draw((CHAR_UC_TABLE  + 8 * ('v' - 'a')), 54, 0);
    sprite_draw((CHAR_UC_TABLE  + 8 * ('e' - 'a')), 63, 0);
    sprite_draw((CHAR_UC_TABLE  + 8 * ('r' - 'a')), 72, 0);
    sprite_draw((CHAR_UC_TABLE  + 8 * ('s' - 'a')), 0, 9);
    sprite_draw((CHAR_UC_TABLE  + 8 * ('c' - 'a')), 9, 9);
    sprite_draw((CHAR_UC_TABLE  + 8 * ('o' - 'a')), 18, 9);
    sprite_draw((CHAR_UC_TABLE  + 8 * ('r' - 'a')), 27, 9);
    sprite_draw((CHAR_UC_TABLE  + 8 * ('e' - 'a')), 36, 9);
    sprite_draw((NUM_TABLE + 8 * (cnt / 100)), 54, 9);
    sprite_draw((NUM_TABLE + 8 * ((cnt / 10) % 10)), 63, 9);
    sprite_draw((NUM_TABLE + 8 * (cnt % 10)), 72, 9);
    while (1);
}
