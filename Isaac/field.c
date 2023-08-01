#include "field.h"

uint8_t h = 48, w = 84;

/*void field_update(display_t* display, field_t* field) {
    for (int q = 0; q < field.s; ++q) {
        LCD_send(&display, SET_PAGE|field.querries[q].page, COMMAND);
        LCD_send(&display, SET_ADDRESS|field.querries[q].adress, COMMAND);
        LCD_send(&display, field.querries[q].byte, DATA);
    }
    field.s = 0;
}

void field_add_query(field_t* field, uint8_t page, uint8_t adress, uint8_t byte) {
    field.querries[field.s].page = page;
    field.querries[field.s].adress = adress;
    field.querries[field.s].byte = byte;
    field.s++;
}*/

void draw(display_t* display, uint8_t page, uint8_t adress, uint8_t byte) {
    LCD_send(display, SET_PAGE|page, COMMAND);
    LCD_send(display, SET_ADDRESS|adress, COMMAND);
    LCD_send(display, byte, DATA);
    LCD_send(display, SET_PAGE|1, COMMAND);
    LCD_send(display, SET_ADDRESS, COMMAND);
    LCD_send(display, 0x00, DATA);
}


void draw_room(display_t* display) {
    LCD_clear(display);
    for (int i = 1; i <= 4; ++i) {
        draw(display, i, 3, 0b11111111);
        draw(display, i, 80, 0b11111111);
    }
    LCD_send(display, SET_PAGE, COMMAND);
    LCD_send(display, SET_ADDRESS, COMMAND);
    for (int i = 0; i < 4; ++i) {
        LCD_send(display, 0b00000011 << (2 * i), DATA);
    }
    for (int i = 4; i < 80; ++i) {
        LCD_send(display, 0b010000000, DATA);
    }
    for (int i = 0; i < 4; ++i) {
        LCD_send(display, 0b00000011 << (6 - 2 * i), DATA);
    }
    LCD_send(display, SET_PAGE|5, COMMAND);
    LCD_send(display, SET_ADDRESS, COMMAND);
    for (int i = 0; i < 4; ++i) {
        LCD_send(display, 0b00000011 << (6 - 2 * i), DATA);
    }
    for (int i = 4; i < 80; ++i) {
        LCD_send(display, 0b00000001, DATA);
    }
    for (int i = 0; i < 4; ++i) {
        LCD_send(display, 0b00000011 << (2 * i), DATA);
    }
}
