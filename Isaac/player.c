#include <stdint.h>
#include "field.h"
#include "player.h"
#include "sprite.h"

int8_t nx, ny;

void player_move(display_t* display, player_t* pl, int8_t dx, int8_t dy) {
    if (!dx && !dy)
        return;
    nx = pl->x + dx;
    ny = pl->y + dy;
    if (dx < 0 && nx < 4 + pl->sprite.dx)
        nx = 4 + pl->sprite.dx;
    else if (dx > 0 && nx > 79 - pl->sprite.dx)
        nx = 79 - pl->sprite.dx;
    if (dy < 0 && ny < 8 + pl->sprite.dy)
        ny = 8 + pl->sprite.dy;
    else if (dy > 0 && ny > 39 - pl->sprite.dy)
        ny = 39 - pl->sprite.dy;
    erase_sprite(display, &pl->sprite, pl->x, pl->y);
    draw_sprite(display, &pl->sprite, nx, ny);
    pl->x = nx;
    pl->y = ny;
}
