#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include <stdint.h>
#include "lcd.h"
#include "player.h"
#include "sprite.h"

typedef struct {
    int8_t x;
    int8_t y;
    sprite_t sprite;
} enemy_t;

void enemy_move(display_t* display, enemy_t* enemy, player_t* player);

uint8_t col(enemy_t *enemy, player_t* player);
#endif // ENEMY_H_INCLUDED
