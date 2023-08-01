#include "drawings.h"
#include "ptr.h"

uint8_t last_player_coord = 3;

void draw_zeros(display_t* display){
    for (int j = 0; j < 6; j++){
    for (int i = 3; i < 57; i++){
        LCD_send(display, SET_ADDRESS | i, COMMAND);
        LCD_send(display, SET_PAGE | j, COMMAND);
        LCD_send(display,0x00, DATA);
        delay(1);
        }}
}

void draw_zeros_full(display_t* display){
    for (int j = 0; j < 6; j++){
    for (int i = 0; i < 84; i++){
        LCD_send(display, SET_ADDRESS | i, COMMAND);
        LCD_send(display, SET_PAGE | j, COMMAND);
        LCD_send(display,0x00, DATA);
        delay(1);
        }}
}


inline void afterscore(display_t* display, int score){

    LCD_send(display, SET_ADDRESS | 15 - 12, COMMAND);
    LCD_send(display, SET_PAGE | 4, COMMAND);
    LCD_send(display, 0b00000011, DATA);
    LCD_send(display, 0b00000100, DATA);
    LCD_send(display, 0b00011000, DATA);
    LCD_send(display, 0b00000100, DATA);
    LCD_send(display, 0b00000011, DATA);

    LCD_send(display, SET_ADDRESS | 21 - 12, COMMAND);
    LCD_send(display, 0b00001110, DATA);
    LCD_send(display, 0b00010001, DATA);
    LCD_send(display, 0b00010001, DATA);
    LCD_send(display, 0b00010001, DATA);
    LCD_send(display, 0b00001110, DATA);
    LCD_send(display, SET_ADDRESS | 27 - 12, COMMAND);
    LCD_send(display, 0b00001111, DATA);
    LCD_send(display, 0b00010000, DATA);
    LCD_send(display, 0b00010000, DATA);
    LCD_send(display, 0b00010000, DATA);
    LCD_send(display, 0b00001111, DATA);
    LCD_send(display, SET_ADDRESS | 33 - 12, COMMAND);
    LCD_send(display, 0b00011111, DATA);
    LCD_send(display, 0b00001001, DATA);
    LCD_send(display, 0b00001001, DATA);
    LCD_send(display, 0b00001001, DATA);
    LCD_send(display, 0b00010110, DATA);
    LCD_send(display, SET_ADDRESS | 45 - 12, COMMAND);
    LCD_send(display, 0b00010111, DATA);
    LCD_send(display, 0b00010101, DATA);
    LCD_send(display, 0b00010101, DATA);
    LCD_send(display, 0b00010101, DATA);
    LCD_send(display, 0b00011101, DATA);
    LCD_send(display, SET_ADDRESS | 51 - 12, COMMAND);
    LCD_send(display, 0b00001110, DATA);
    LCD_send(display, 0b00010001, DATA);
    LCD_send(display, 0b00010001, DATA);
    LCD_send(display, 0b00010001, DATA);
    LCD_send(display, 0b00010001, DATA);
    LCD_send(display, SET_ADDRESS | 57 - 12, COMMAND);
    LCD_send(display, 0b00001110, DATA);
    LCD_send(display, 0b00010001, DATA);
    LCD_send(display, 0b00010001, DATA);
    LCD_send(display, 0b00010001, DATA);
    LCD_send(display, 0b00001110, DATA);
    LCD_send(display, SET_ADDRESS | 63 - 12, COMMAND);
    LCD_send(display, 0b00011111, DATA);
    LCD_send(display, 0b00001001, DATA);
    LCD_send(display, 0b00001001, DATA);
    LCD_send(display, 0b00001001, DATA);
    LCD_send(display, 0b00010110, DATA);
    LCD_send(display, SET_ADDRESS | 69 - 12, COMMAND);
    LCD_send(display, 0b00011111, DATA);
    LCD_send(display, 0b00010101, DATA);
    LCD_send(display, 0b00010101, DATA);
    LCD_send(display, 0b00010101, DATA);
    LCD_send(display, 0b00010101, DATA);
    LCD_send(display, SET_ADDRESS | 75 - 12, COMMAND);
    LCD_send(display, 0b00001010, DATA);
    draw_score(display, score);

}

void draw_pause(display_t* display){
    draw_zeros(display);

    LCD_send(display, SET_ADDRESS | 16, COMMAND);
    LCD_send(display, SET_PAGE | 2, COMMAND);
    LCD_send(display, 0b00011111, DATA);
    LCD_send(display, 0b00000101, DATA);
    LCD_send(display, 0b00000101, DATA);
    LCD_send(display, 0b00000101, DATA);
    LCD_send(display, 0b00000010, DATA);
    LCD_send(display, SET_ADDRESS | 22, COMMAND);
    LCD_send(display, 0b00011000, DATA);
    LCD_send(display, 0b00000110, DATA);
    LCD_send(display, 0b00000101, DATA);
    LCD_send(display, 0b00000110, DATA);
    LCD_send(display, 0b00011000, DATA);
    LCD_send(display, SET_ADDRESS | 28, COMMAND);
    LCD_send(display, 0b00001111, DATA);
    LCD_send(display, 0b00010000, DATA);
    LCD_send(display, 0b00010000, DATA);
    LCD_send(display, 0b00010000, DATA);
    LCD_send(display, 0b00001111, DATA);
    LCD_send(display, SET_ADDRESS | 34, COMMAND);
    LCD_send(display, 0b00010111, DATA);
    LCD_send(display, 0b00010101, DATA);
    LCD_send(display, 0b00010101, DATA);
    LCD_send(display, 0b00010101, DATA);
    LCD_send(display, 0b00011101, DATA);
    LCD_send(display, SET_ADDRESS | 40, COMMAND);
    LCD_send(display, 0b00011111, DATA);
    LCD_send(display, 0b00010101, DATA);
    LCD_send(display, 0b00010101, DATA);
    LCD_send(display, 0b00010101, DATA);
    LCD_send(display, 0b00010101, DATA);

}

void draw_gameover(display_t* display, int score){
    draw_zeros_full(display);

    LCD_send(display, SET_ADDRESS | 4 + 12, COMMAND);
    LCD_send(display, SET_PAGE | 2, COMMAND);
    LCD_send(display, 0b00011111, DATA);
    LCD_send(display, 0b00010001, DATA);
    LCD_send(display, 0b00010101, DATA);
    LCD_send(display, 0b00010101, DATA);
    LCD_send(display, 0b00011101, DATA);

    LCD_send(display, SET_ADDRESS | 10 + 12, COMMAND);
    LCD_send(display, 0b00011000, DATA);
    LCD_send(display, 0b00000110, DATA);
    LCD_send(display, 0b00000101, DATA);
    LCD_send(display, 0b00000110, DATA);
    LCD_send(display, 0b00011000, DATA);
    LCD_send(display, SET_ADDRESS | 16 + 12, COMMAND);
    LCD_send(display, 0b00011111, DATA);
    LCD_send(display, 0b00000010, DATA);
    LCD_send(display, 0b00000100, DATA);
    LCD_send(display, 0b00000010, DATA);
    LCD_send(display, 0b00011111, DATA);
    LCD_send(display, SET_ADDRESS | 22 + 12, COMMAND);
    LCD_send(display, 0b00011111, DATA);
    LCD_send(display, 0b00010101, DATA);
    LCD_send(display, 0b00010101, DATA);
    LCD_send(display, 0b00010101, DATA);
    LCD_send(display, 0b00010101, DATA);
    LCD_send(display, SET_ADDRESS | 33 + 12, COMMAND);
    LCD_send(display, 0b00001110, DATA);
    LCD_send(display, 0b00010001, DATA);
    LCD_send(display, 0b00010001, DATA);
    LCD_send(display, 0b00010001, DATA);
    LCD_send(display, 0b00001110, DATA);
    LCD_send(display, SET_ADDRESS | 39 + 12, COMMAND);
    LCD_send(display, 0b00000011, DATA);
    LCD_send(display, 0b00001100, DATA);
    LCD_send(display, 0b00010000, DATA);
    LCD_send(display, 0b00001100, DATA);
    LCD_send(display, 0b00000011, DATA);
    LCD_send(display, SET_ADDRESS | 45 + 12, COMMAND);
    LCD_send(display, 0b00011111, DATA);
    LCD_send(display, 0b00010101, DATA);
    LCD_send(display, 0b00010101, DATA);
    LCD_send(display, 0b00010101, DATA);
    LCD_send(display, 0b00010101, DATA);
    LCD_send(display, SET_ADDRESS | 51 + 12, COMMAND);
    LCD_send(display, 0b00011111, DATA);
    LCD_send(display, 0b00001001, DATA);
    LCD_send(display, 0b00001001, DATA);
    LCD_send(display, 0b00001001, DATA);
    LCD_send(display, 0b00010110, DATA);
    afterscore(display, score);


}


void draw_win(display_t* display, int score){
    draw_zeros_full(display);

    LCD_send(display, SET_ADDRESS | 15, COMMAND);
    LCD_send(display, SET_PAGE | 2, COMMAND);
    LCD_send(display, 0b00000011, DATA);
    LCD_send(display, 0b00000100, DATA);
    LCD_send(display, 0b00011000, DATA);
    LCD_send(display, 0b00000100, DATA);
    LCD_send(display, 0b00000011, DATA);

    LCD_send(display, SET_ADDRESS | 21, COMMAND);
    LCD_send(display, 0b00001110, DATA);
    LCD_send(display, 0b00010001, DATA);
    LCD_send(display, 0b00010001, DATA);
    LCD_send(display, 0b00010001, DATA);
    LCD_send(display, 0b00001110, DATA);
    LCD_send(display, SET_ADDRESS | 27, COMMAND);
    LCD_send(display, 0b00001111, DATA);
    LCD_send(display, 0b00010000, DATA);
    LCD_send(display, 0b00010000, DATA);
    LCD_send(display, 0b00010000, DATA);
    LCD_send(display, 0b00001111, DATA);
    LCD_send(display, SET_ADDRESS | 39, COMMAND);
    LCD_send(display, 0b00001111, DATA);
    LCD_send(display, 0b00010000, DATA);
    LCD_send(display, 0b00001100, DATA);
    LCD_send(display, 0b00010000, DATA);
    LCD_send(display, 0b00001111, DATA);
    LCD_send(display, SET_ADDRESS | 45, COMMAND);
    LCD_send(display, 0b00001110, DATA);
    LCD_send(display, 0b00010001, DATA);
    LCD_send(display, 0b00010001, DATA);
    LCD_send(display, 0b00010001, DATA);
    LCD_send(display, 0b00001110, DATA);
    LCD_send(display, SET_ADDRESS | 51, COMMAND);
    LCD_send(display, 0b00011111, DATA);
    LCD_send(display, 0b00000010, DATA);
    LCD_send(display, 0b00000100, DATA);
    LCD_send(display, 0b00001000, DATA);
    LCD_send(display, 0b00011111, DATA);
    LCD_send(display, SET_ADDRESS | 57, COMMAND);
    LCD_send(display, 0b00010111, DATA);
    LCD_send(display, 0b00000000, DATA);
    LCD_send(display, 0b00010111, DATA);
    LCD_send(display, 0b00000000, DATA);
    LCD_send(display, 0b00010111, DATA);
    afterscore(display, score);


}





void draw_score(display_t* display, int score){

    int l1 = 0;
    int l2 = 0;
    int l3 = 0;

    if (score > 9){
    l2 = score/10%10;
    }
    if (score > 99){
    l1 = score/100;
    }
    l3 = score%10;


    draw_number(display, 67, 4, l1);
    draw_number(display, 71, 4, l2);
    draw_number(display, 75, 4, l3);
    delay(5);

}

void draw_road(display_t* display, uint8_t* line){

    for (int i = 0; i < 6; i++){

        LCD_send(display, SET_ADDRESS | 20, COMMAND);
        LCD_send(display, SET_PAGE | i, COMMAND);
        LCD_send(display, line[i], DATA);
        delay(2);

    }

    for (int i = 0; i < 6; i++){

        LCD_send(display, SET_ADDRESS | 39, COMMAND);
        LCD_send(display, SET_PAGE | i, COMMAND);
        LCD_send(display, line[i], DATA);
        delay(10);

    }

}

void draw_overlay(display_t* display){

    for (int i = 0; i < 7; i++)
    {
        LCD_send(display, SET_ADDRESS | 1, COMMAND);
        LCD_send(display, SET_PAGE | i, COMMAND);
        LCD_send(display, 0xFF, DATA);

    }
    for (int i = 0; i < 7; i++)
    {
        LCD_send(display, SET_ADDRESS | 58, COMMAND);
        LCD_send(display, SET_PAGE | i, COMMAND);
        LCD_send(display, 0xFF, DATA);

    }
    for (int i = 0; i < 7; i++)
    {
        LCD_send(display, SET_ADDRESS | 60, COMMAND);
        LCD_send(display, SET_PAGE | i, COMMAND);
        LCD_send(display, 0xFF, DATA);

    }
    LCD_send(display, SET_ADDRESS | 63, COMMAND);
    LCD_send(display, SET_PAGE | 1, COMMAND);
    LCD_send(display, 0b00010111, DATA);

    LCD_send(display, SET_PAGE | 1, COMMAND);
    LCD_send(display, 0b00010101, DATA);

    LCD_send(display, SET_PAGE | 1, COMMAND);
    LCD_send(display, 0b00011101, DATA);

    LCD_send(display, SET_ADDRESS | 67, COMMAND);
    LCD_send(display, SET_PAGE | 1, COMMAND);
    LCD_send(display, 0b00011111, DATA);

    LCD_send(display, SET_PAGE | 1, COMMAND);
    LCD_send(display, 0b00000101, DATA);

    LCD_send(display, SET_PAGE | 1, COMMAND);
    LCD_send(display, 0b00000010, DATA);

    LCD_send(display, SET_ADDRESS | 71, COMMAND);
    LCD_send(display, SET_PAGE | 1, COMMAND);
    LCD_send(display, 0b00011111, DATA);

    LCD_send(display, SET_PAGE | 1, COMMAND);
    LCD_send(display, 0b00010101, DATA);

    LCD_send(display, SET_PAGE | 1, COMMAND);
    LCD_send(display, 0b00010101, DATA);


    LCD_send(display, SET_ADDRESS | 75, COMMAND);
    LCD_send(display, SET_PAGE | 1, COMMAND);
    LCD_send(display, 0b00011111, DATA);

    LCD_send(display, SET_PAGE | 1, COMMAND);
    LCD_send(display, 0b00010101, DATA);

    LCD_send(display, SET_PAGE | 1, COMMAND);
    LCD_send(display, 0b00010101, DATA);

    LCD_send(display, SET_ADDRESS | 79, COMMAND);
    LCD_send(display, SET_PAGE | 1, COMMAND);
    LCD_send(display, 0b00011111, DATA);

    LCD_send(display, SET_PAGE | 1, COMMAND);
    LCD_send(display, 0b00010001, DATA);

    LCD_send(display, SET_PAGE | 1, COMMAND);
    LCD_send(display, 0b00001110, DATA);


    LCD_send(display, SET_ADDRESS | 63, COMMAND);
    LCD_send(display, SET_PAGE | 3, COMMAND);
    LCD_send(display, 0b00010111, DATA);

    LCD_send(display, SET_PAGE | 3, COMMAND);
    LCD_send(display, 0b00010101, DATA);

    LCD_send(display, SET_PAGE | 3, COMMAND);
    LCD_send(display, 0b00011101, DATA);

    LCD_send(display, SET_ADDRESS | 67, COMMAND);
    LCD_send(display, SET_PAGE | 3, COMMAND);
    LCD_send(display, 0b00011111, DATA);

    LCD_send(display, SET_PAGE | 3, COMMAND);
    LCD_send(display, 0b00010001, DATA);

    LCD_send(display, SET_PAGE | 3, COMMAND);
    LCD_send(display, 0b00010001, DATA);

    LCD_send(display, SET_ADDRESS | 71, COMMAND);
    LCD_send(display, SET_PAGE | 3, COMMAND);
    LCD_send(display, 0b00011111, DATA);

    LCD_send(display, SET_PAGE | 3, COMMAND);
    LCD_send(display, 0b00010001, DATA);

    LCD_send(display, SET_PAGE | 3, COMMAND);
    LCD_send(display, 0b00011111, DATA);

    LCD_send(display, SET_ADDRESS | 75, COMMAND);
    LCD_send(display, SET_PAGE | 3, COMMAND);
    LCD_send(display, 0b00011111, DATA);

    LCD_send(display, SET_PAGE | 3, COMMAND);
    LCD_send(display, 0b00000101, DATA);

    LCD_send(display, SET_PAGE | 3, COMMAND);
    LCD_send(display, 0b00011010, DATA);



    LCD_send(display, SET_ADDRESS | 79, COMMAND);
    LCD_send(display, SET_PAGE | 3, COMMAND);
    LCD_send(display, 0b00011111, DATA);

    LCD_send(display, SET_PAGE | 3, COMMAND);
    LCD_send(display, 0b00010101, DATA);

    LCD_send(display, SET_PAGE | 3, COMMAND);
    LCD_send(display, 0b00010101, DATA);


}

void draw_number(display_t* display, uint16_t x, uint16_t page, uint8_t number){

    if (number == 0){
    LCD_send(display, SET_ADDRESS | x, COMMAND);
    LCD_send(display, SET_PAGE | page, COMMAND);
    LCD_send(display, 0b00011111, DATA);

    LCD_send(display, SET_PAGE | page, COMMAND);
    LCD_send(display, 0b00010001, DATA);

    LCD_send(display, SET_PAGE | page, COMMAND);
    LCD_send(display, 0b00011111, DATA);
    }

    if (number == 1){
    LCD_send(display, SET_ADDRESS | x, COMMAND);
    LCD_send(display, SET_PAGE | page, COMMAND);
    LCD_send(display, 0b00000100, DATA);

    LCD_send(display, SET_PAGE | page, COMMAND);
    LCD_send(display, 0b00000010, DATA);

    LCD_send(display, SET_PAGE | page, COMMAND);
    LCD_send(display, 0b00011111, DATA);
    }

    if (number == 2){
    LCD_send(display, SET_ADDRESS | x, COMMAND);
    LCD_send(display, SET_PAGE | page, COMMAND);
    LCD_send(display, 0b00011010, DATA);

    LCD_send(display, SET_PAGE | page, COMMAND);
    LCD_send(display, 0b00010101, DATA);

    LCD_send(display, SET_PAGE | page, COMMAND);
    LCD_send(display, 0b00010011, DATA);
    }

    if (number == 3){
    LCD_send(display, SET_ADDRESS | x, COMMAND);
    LCD_send(display, SET_PAGE | page, COMMAND);
    LCD_send(display, 0b00010101, DATA);

    LCD_send(display, SET_PAGE | page, COMMAND);
    LCD_send(display, 0b00010101, DATA);

    LCD_send(display, SET_PAGE | page, COMMAND);
    LCD_send(display, 0b00001010, DATA);
    }

    if (number == 4){
    LCD_send(display, SET_ADDRESS | x, COMMAND);
    LCD_send(display, SET_PAGE | page, COMMAND);
    LCD_send(display, 0b00000111, DATA);

    LCD_send(display, SET_PAGE | page, COMMAND);
    LCD_send(display, 0b00000100, DATA);

    LCD_send(display, SET_PAGE | page, COMMAND);
    LCD_send(display, 0b00011111, DATA);
    }

    if (number == 5){
    LCD_send(display, SET_ADDRESS | x, COMMAND);
    LCD_send(display, SET_PAGE | page, COMMAND);
    LCD_send(display, 0b00010111, DATA);

    LCD_send(display, SET_PAGE | page, COMMAND);
    LCD_send(display, 0b00010101, DATA);

    LCD_send(display, SET_PAGE | page, COMMAND);
    LCD_send(display, 0b00001001, DATA);
    }

    if (number == 6){
    LCD_send(display, SET_ADDRESS | x, COMMAND);
    LCD_send(display, SET_PAGE | page, COMMAND);
    LCD_send(display, 0b00011111, DATA);

    LCD_send(display, SET_PAGE | page, COMMAND);
    LCD_send(display, 0b00010101, DATA);

    LCD_send(display, SET_PAGE | page, COMMAND);
    LCD_send(display, 0b00011101, DATA);
    }

    if (number == 7){
    LCD_send(display, SET_ADDRESS | x, COMMAND);
    LCD_send(display, SET_PAGE | page, COMMAND);
    LCD_send(display, 0b00000001, DATA);

    LCD_send(display, SET_PAGE | page, COMMAND);
    LCD_send(display, 0b00011001, DATA);

    LCD_send(display, SET_PAGE | page, COMMAND);
    LCD_send(display, 0b00000111, DATA);
    }
    if (number == 8){
    LCD_send(display, SET_ADDRESS | x, COMMAND);
    LCD_send(display, SET_PAGE | page, COMMAND);
    LCD_send(display, 0b00011111, DATA);

    LCD_send(display, SET_PAGE | page, COMMAND);
    LCD_send(display, 0b00010101, DATA);

    LCD_send(display, SET_PAGE | page, COMMAND);
    LCD_send(display, 0b00011111, DATA);
    }
    if (number == 9){
    LCD_send(display, SET_ADDRESS | x, COMMAND);
    LCD_send(display, SET_PAGE | page, COMMAND);
    LCD_send(display, 0b00010111, DATA);

    LCD_send(display, SET_PAGE | page, COMMAND);
    LCD_send(display, 0b00010101, DATA);

    LCD_send(display, SET_PAGE | page, COMMAND);
    LCD_send(display, 0b00001111, DATA);
    }

}

void last_bit(display_t* display){

    LCD_send(display, SET_ADDRESS | 83, COMMAND);
    LCD_send(display, SET_PAGE, COMMAND);
    LCD_send(display, 0b00000000, DATA);

}

void sprite_draw(display_t* display, uint8_t* arr, uint8_t* arr1, uint8_t x, uint8_t y){
    uint8_t Page = y / 8;
    uint8_t shift = y % 8;
    uint8_t mask =  0;
    uint8_t datapx = 0;
    for (uint8_t i = 0; i < TILE_SIZE; ++i){
        LCD_send(display, SET_PAGE | Page, COMMAND); // hight
        LCD_send(display, (SET_ADDRESS | x + i), COMMAND);
        mask = 1 << (8 - shift);
        mask = mask - 1;
        datapx = arr[i] & mask;
        datapx = datapx << shift;
        LCD_send(display, datapx, DATA);

        LCD_send(display, SET_PAGE | Page + 1, COMMAND); // down
        LCD_send(display, (SET_ADDRESS | x + i), COMMAND);
        mask = 1 << shift;
        mask = mask - 1;
        mask = mask << (8 - shift);
        datapx = arr[i] & mask;
        datapx = datapx >> (8 - shift);
        datapx |= arr1[i] << shift;
        LCD_send(display, datapx, DATA);
    }
}


void sprite_draww(display_t* display, uint8_t* arr, uint8_t x, uint8_t y){
    uint8_t Page = y / 8;
    uint8_t shift = y % 8;
    uint8_t mask =  0;
    uint8_t datapx = 0;
    for (uint8_t i = 0; i < TILE_SIZE; ++i){
        LCD_send(display, SET_PAGE | Page, COMMAND); // hight
        LCD_send(display, (SET_ADDRESS | x + i), COMMAND);
        mask = 1 << (8 - shift);
        mask = mask - 1;
        datapx = arr[i] & mask;
        datapx = datapx << shift;
        LCD_send(display, datapx, DATA);

        LCD_send(display, SET_PAGE | Page + 1, COMMAND); // down
        LCD_send(display, (SET_ADDRESS | x + i), COMMAND);
        mask = 1 << shift;
        mask = mask - 1;
        mask = mask << (8 - shift);
        datapx = arr[i] & mask;
        datapx = datapx >> (8 - shift);
        LCD_send(display, datapx, DATA);
        }
}
