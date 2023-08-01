#include <stdint.h>
#include "memory.h"
#include "tim4.h"
#include "lcd.h"
#include "joystick.h"
#include "field.h"
#include "player.h"
#include "enemy.h"

#define MAX_ENEMIES 3

#ifndef __PTR_H__
#define __PTR_H__

#define TILE_SIZE 8

#define NUM_TABLE (volatile uint8_t*)0x4000
#define NUM_TABLE_SIZE 10

#define CHAR_UC_TABLE (volatile uint8_t*)0x4050
#define CHAR_UC_TABLE_SIZE 26

#define CHAR_LC_TABLE (volatile uint8_t*)0x4120
#define CHAR_LC_TABLE_SIZE 26


#endif

void main() {
    __asm__("rim");
    display_t display;
    LCD_init(&display, DIV_2);
    TIM4_init();
    joystick_init();

    draw_room(&display);

    player_t player;
    player.x = w / 2;
    player.y = h / 2;
    player.sprite.arr[0] = 0b00011100;
    player.sprite.arr[1] = 0b00110110;
    player.sprite.arr[2] = 0b01100011;
    player.sprite.arr[3] = 0b01000001;
    player.sprite.arr[4] = 0b01100011;
    player.sprite.arr[5] = 0b00110110;
    player.sprite.arr[6] = 0b00011100;
    player.sprite.arr[7] = 0b00000000;
    player.sprite.en = 0b01111111;
    player.sprite.cx = 3;
    player.sprite.cy = 3;
    player.sprite.dx = 4;
    player.sprite.dy = 4;
    draw_sprite(&display, &player.sprite, player.x, player.y);

    enemy_t enemies[MAX_ENEMIES];
    enemies[0].x = 8;
    enemies[0].y = 12;
    enemies[0].sprite.arr[0] = 0b00011100;
    enemies[0].sprite.arr[1] = 0b00111110;
    enemies[0].sprite.arr[2] = 0b01111111;
    enemies[0].sprite.arr[3] = 0b01111111;
    enemies[0].sprite.arr[4] = 0b01111111;
    enemies[0].sprite.arr[5] = 0b00111110;
    enemies[0].sprite.arr[6] = 0b00011100;
    enemies[0].sprite.arr[7] = 0b00000000;
    enemies[0].sprite.en = 0b01111111;
    enemies[0].sprite.cx = 3;
    enemies[0].sprite.cy = 3;
    enemies[0].sprite.dx = 4;
    enemies[0].sprite.dy = 4;
    for(uint8_t i = 0; i < MAX_ENEMIES; ++i) {
        enemies[i] = enemies[0];
        if (i) {
            enemies[i].x = enemies[i - 1].x + 8;
            enemies[i].y = enemies[i - 1].y + 8;
        }
        draw_sprite(&display, &enemies[i].sprite, enemies[i].x, enemies[i].y);
    }
    int16_t dxp, dyp;
    int8_t dx, dy;
    while(1) {
        dxp = ADC_get_vec_from_channel(Y_CH, -1);
        dyp = ADC_get_vec_from_channel(X_CH, 1);
        dx = dxp / 124;
        dy = dyp / 124;
        player_move(&display, &player, dx, dy);
        for(uint8_t i = 0; i < MAX_ENEMIES; ++i)
            enemy_move(&display, &enemies[i], &player);
        for(uint8_t i = 0; i < MAX_ENEMIES; ++i)
            if (col(&enemies[i], &player))
                TIM4_sleep(123123);
        TIM4_sleep(200);
    }
}
