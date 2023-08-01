#include "enemy.h"

int8_t enx, eny;
void enemy_move(display_t* display, enemy_t* enemy, player_t* player) {
    if (enemy->x < player->x)
        enx = enemy->x + 1;
    else if (enemy->x > player->x)
        enx = enemy->x - 1;
    if (enemy->y < player->y)
        eny = enemy->y + 1;
    else if (enemy->y > player->y)
        eny = enemy->y - 1;
    erase_sprite(display, &enemy->sprite, enemy->x, enemy->y);
    draw_sprite(display, &enemy->sprite, enx, eny);
    enemy->x = enx;
    enemy->y = eny;
}

inline uint8_t abs(int8_t a) {
    return a >= 0 ? a : -a;
}

uint8_t col(enemy_t *enemy, player_t* player) {
    return (abs(enemy->x - player->x) < enemy->sprite.dx + player->sprite.dx && abs(enemy->y - player->y) < enemy->sprite.dy + player->sprite.dy);
}
