#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <stdint.h>
#include "lcd.h"
#include "sprite.h"

typedef struct{
    int8_t x;
    int8_t y;
    sprite_t sprite;
}player_t;

void player_move(display_t* disp, player_t* pl, int8_t x, int8_t y);

#endif // PLAYER_H_INCLUDED
