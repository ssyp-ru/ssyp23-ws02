#ifndef _drawings_H_
#define _drawings_H_
#include "LCD.h"
#include "timer.h"
#include <stdint.h>

void draw_zeros(display_t* display);
void draw_overlay(display_t* display);
void draw_score(display_t* display, int score);
void draw_road(display_t* display, uint8_t* line);
void last_bit(display_t* display);
void draw_number(display_t* display, uint16_t x, uint16_t page, uint8_t number);
void sprite_draw(display_t* display, uint8_t* arr, uint8_t* arr1, uint8_t x, uint8_t y);
void sprite_draww(display_t* display, uint8_t* arr, uint8_t x, uint8_t y);
void draw_gameover(display_t* display, int score);
void draw_zeros_full(display_t* display);
void draw_pause(display_t* display);
void draw_win(display_t* display, int score);

#endif
