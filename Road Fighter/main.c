#include "joystick.h"
#include "timer.h"
#include "LCD.h"
#include "drawings.h"
#include <stdint.h>
#include "ptr.h"

uint8_t dx = 0b00000000;
uint8_t line[6];
uint8_t speed = 1;
int score = 0;
int enemy_y = 100;
uint8_t enemy_x = 0;
uint8_t player_x = 26;
uint8_t flagkp = 0;
uint8_t score_inc = 0;
uint8_t clear_bit = 0;
uint8_t collided = 0;
uint8_t win = 0;

uint8_t random()
{
    static uint8_t counter = 0;
    counter = (counter + 1) % RANDOM_TABLE_SIZE;
    return (RANDOM_TABLE)[counter] % 3;
}


void enemy_logic()
{

    if (enemy_y > 48)
    {

        uint8_t r = random();
        enemy_y = -12;

        if (r == 0)
        {
            enemy_x = 7;
        }

        if (r == 1)
        {
            enemy_x = 26;
        }

        if (r == 2)
        {
            enemy_x = 45;
        }

    }

    if (enemy_y <= 48)
    {
        enemy_y++;
    }

}

void move_road_bit()
{
    if (speed > 0){
    enemy_logic();
    uint8_t f = 0;
    uint8_t g = 0;
    f = (line[5] & 0b10000000) ? 1 : 0;
    line[5] <<= 1;
    g = (line[4] & 0b10000000) ? 1 : 0;
    line[4] <<= 1;
    if (f == 1)
    {
        line[4] |= 0b00000001;
    }
    f = g;
    g = (line[3] & 0b10000000) ? 1 : 0;
    line[3] <<= 1;
    if (f == 1)
    {
        line[3] |= 0b00000001;
    }
    f = g;
    g = (line[2] & 0b10000000) ? 1 : 0;
    line[2] <<= 1;
    if (f == 1)
    {
        line[2] |= 0b00000001;
    }
    f = g;
    g = (line[1] & 0b10000000) ? 1 : 0;
    line[1] <<= 1;
    if (f == 1)
    {
        line[1] |= 0b00000001;
    }
    f = g;
    g = (line[0] & 0b10000000) ? 1 : 0;
    line[0] <<= 1;
    if (f == 1)
    {
        line[0] |= 0b00000001;
    }
    if (g == 1)
    {
        line[5] |= 0b00000001;
    }}
    if (speed > 1)
    {
        enemy_logic();
        uint8_t f = 0;
        uint8_t g = 0;
        f = (line[5] & 0b10000000) ? 1 : 0;
        line[5] <<= 1;
        g = (line[4] & 0b10000000) ? 1 : 0;
        line[4] <<= 1;
        if (f == 1)
        {
            line[4] |= 0b00000001;
        }
        f = g;
        g = (line[3] & 0b10000000) ? 1 : 0;
        line[3] <<= 1;
        if (f == 1)
        {
            line[3] |= 0b00000001;
        }
        f = g;
        g = (line[2] & 0b10000000) ? 1 : 0;
        line[2] <<= 1;
        if (f == 1)
        {
            line[2] |= 0b00000001;
        }
        f = g;
        g = (line[1] & 0b10000000) ? 1 : 0;
        line[1] <<= 1;
        if (f == 1)
        {
            line[1] |= 0b00000001;
        }
        f = g;
        g = (line[0] & 0b10000000) ? 1 : 0;
        line[0] <<= 1;
        if (f == 1)
        {
            line[0] |= 0b00000001;
        }
        if (g == 1)
        {
            line[5] |= 0b00000001;
        }

    }


}







inline int abs(int a)
{
    return a >= 0 ? a : -a;
}


void is_collide()
{

    if ((enemy_y > 23)&&(enemy_y < 40))
    {

        if (abs(player_x - enemy_x) < 8)
        {

            collided = 1;

        }

    }



}




void game_logic(display_t* display)
{

    move_road_bit();
    if ((dx & 0b00001000) == 0b00001000)
    {

        if ((speed < 2) && (flagkp == 0))
        {
            speed++;
            draw_zeros(display);
        }
        flagkp = 1;
    }
    if ((dx & 0b00000100) == 0b00000100)
    {

        if ((speed > 0) && (flagkp == 0))
        {
            speed--;
            if (speed > 0){
            draw_zeros(display);}
            if (speed == 0){
            draw_pause(display);}
        }
        flagkp = 1;
    }
    if ((dx & 0b00001100) == 0b00000000)
    {
        flagkp = 0;
    }


    score_inc += speed;
    if (score_inc > 47)
    {

        score_inc = 0;
        score += speed;

    }
    if (speed > 0){
    if ((dx & 0b00010000) == 0b00010000)
    {

        if (player_x > 2)
        {
            player_x--;
            clear_bit = player_x + 8;
        }
    }
    if ((dx & 0b00100000) == 0b00100000)
    {

        if (player_x < 50)
        {

            player_x++;
            clear_bit = player_x - 1;
        }
    }
    }
    is_collide();
    if (score > 200){

        win = 1;

    }




}

void draw_logic(display_t* display)
{
    //draw_player(display, player_x);
    if (speed > 0){
    LCD_send(display, SET_ADDRESS | clear_bit, COMMAND);
    LCD_send(display, SET_PAGE | 4, COMMAND);
    LCD_send(display,0x00, DATA);
    delay(10);
    LCD_send(display, SET_ADDRESS | clear_bit, COMMAND);
    LCD_send(display, SET_PAGE | 5, COMMAND);
    LCD_send(display,0x00, DATA);
    delay(10);



    sprite_draww(display, BOX_TABLE, enemy_x, enemy_y);

    sprite_draw(display, P2_TABLE, P1_TABLE, player_x, 32);

    //sprite_draw(display, E2_TABLE, E1_TABLE, enemy_x, enemy_y);
    draw_road(display, line);
    }


    draw_number(display, 71, 2, speed);
    draw_score(display, score);

}



void main(void)
{
    line[0] = 0b11111111;
    line[1] = 0b00000000;
    line[2] = 0b11111111;
    line[3] = 0b00000000;
    line[4] = 0b11111111;
    line[5] = 0b00000000;

    timer_init();
    display_t display;
    LCD_init(&display, 2);
    //LCD_clear(&display);
    draw_zeros_full(&display);
    draw_overlay(&display);
    draw_score(&display, score);

    //sprite_draw(&display, P1_TABLE, 25, 43);





    joystick_init();
    while(1)
    {
        game_logic(&display);

        if (collided)
        {
           // draw_number(&display, 4, 3, 8);
           // LCD_init(&display, 2);
            draw_gameover(&display, score);
            last_bit(&display);
            break;
        }
        if (win)
        {
           // draw_number(&display, 4, 3, 8);
           // LCD_init(&display, 2);
            draw_win(&display, score);
            last_bit(&display);
            break;
        }
        draw_logic(&display);
        last_bit(&display);

        /*LCD_send(&display, SET_ADDRESS | 83, COMMAND);
        LCD_send(&display, SET_PAGE, COMMAND);
        LCD_send(&display, 0b00000001, DATA);
        //LCD_send(&display, 0xFF, DATA);
        */
        //LCD_clear(&display);
        dx = joystick_state();
    }
    while(1);
}
