#ifndef FIELD_H_INCLUDED
#define FIELD_H_INCLUDED

#include "lcd.h"

extern uint8_t h, w;

/*const uint16_t MAX_S = 504;

typedef struct{
    uint8_t page, adress, byte;
}query_t;

typedef struct{
    // uint8_t arr[6][84];
    query_t querries[MAX_S];
    uint16_t s = 0;
}field_t;

void field_update(display_t* display, field_t* field);

void field_add_query(field_t* field, uint8_t page, uint8_t adress, uint8_t byte);*/

void draw(display_t* display, uint8_t page, uint8_t adress, uint8_t byte);

void draw_room(display_t* display);

#endif // FIELD_H_INCLUDED
