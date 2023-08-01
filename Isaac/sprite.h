#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED

#include "lcd.h"

typedef struct {
    uint8_t arr[8];
    uint8_t en;
    uint8_t dx;
    uint8_t dy;
    int8_t cx;
    int8_t cy;
} sprite_t;

void erase_sprite(display_t* display, sprite_t* sprite, uint8_t x, uint8_t y);

void draw_sprite(display_t* display, sprite_t* sprite, uint8_t x, uint8_t y);

#endif // SPRITE_H_INCLUDED
