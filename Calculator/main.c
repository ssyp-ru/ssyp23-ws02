/*#define PE_ODR (*(volatile char*)0x5014)
#define PE_IDR (*(volatile char*)0x5015)
#define PE_DDR (*(volatile char*)0x5016)
#define PE_CR1 (*(volatile char*)0x5017)
#define PE_CR2 (*(volatile char*)0x5018)*/
#include <stdint.h>
#include "symb.h"
#include "LCD.h"

#define NULL 0x0000

uint8_t is_ovf(int32_t num){
    return (num > 10e9);
}

void itoa(int64_t num, char* buf){
    uint8_t i = 0;
    if (num == 0)
        buf[i++] = '0';
    for (; num > 0 && i < 16; i++, num /= 10)
        buf[i] = num % 10 + '0';
    buf[i] = '\0';
}

void redraw(char* first, char* second){
    LCD_clear();
    LCD_set_pos(15, 1);
    for (; *first != '\0'; first++)
        LCD_send_byte(*first, DATA);
    LCD_set_pos(15, 0);
    for (uint8_t i = 0; second[i] != '\0' && i < 16; i++)
        LCD_send_byte(second[i], DATA);
}

void strcat(char* to, char* from){
    char tmp[34];
    uint8_t i;
    for (i = 0; to[i] != '\0'; i++)
        tmp[i] = to[i];
    tmp[i] = '\0';
    for (i = 0; from[i] != '\0'; i++)
        to[i] = from[i];
    for (uint8_t j = 0; tmp[j] != '\0'; i++, j++)
        to[i] = tmp[j];
    to[i] = '\0';
}

void main(void)
{
    //int sum = 0;
    char last = 0;
    char first[17] = "";
    char second[34] = "";
    int32_t f_num, s_num, res;
    res = 0;
    //char niz[17] = "0";
    //int8_t lenv = 0;
    //int8_t lenn = 0;
    PD_DDR = 0b11110000;
    PD_CR1 = 0b11111111;
    PD_CR2 = 0b11110000;
    LCD_init();
    /*PE_DDR |= 1 << 5;
    PE_CR1 |= 1 << 5;
    PE_CR2 |= 1 << 5;*/
    while(1)
    {
        char sym = chemyravno();
        //LCD_clear();
        if (last != sym){
            last = sym;
            if ((sym >= '0') && (sym <= '9') && (res < 10e9))
                res = res * 10 + (sym - '0');
            itoa(res, first);
            //first[0] = sym;
            //first[1] = '\0';
            redraw(first, second);
        }
    }
        /*if (niz == '0'){
            vse = sym;
        }else{
            if ((sym == '=') || (sym == '+') || (sym == '-') || (sym == ' ') || (sym == '/') || (sym == '*')){
                verh += niz+sym;
                if ((sym == '=') || (sym == ' ')){
                    if (sym == '='){
                    //cверху выражение, снизу число
                        niz = chet(verh);
                        lenn = 0; //zamenit
                        for(int8_t i = 0; i<lenv; i++){
                            LCD_set_pos(i, 0);
                            LCD_send_char(verh[i]);
                        }
                        for(int8_t i = 0; i<lenn; i++){
                            LCD_set_pos(31-i, 1);
                            LCD_send_char(niz[lenn-1-i]);
                        }
                    }else{
                    //снизу 0
                        verh = '\0';
                        niz = '0';
                        LCD_set_pos(31, 1);
                        LCD_send_char('0');
                    }
                }else{
                //сверху выражение, снизу 0
                    lenv+=1+lenn;
                    lenn = 0;
                    niz = '0';
                    for(int8_t i = 0; i<lenv; i++){
                        LCD_set_pos(i, 0);
                        LCD_send_char(verh[i]);
                    }
                    LCD_set_pos(31, 1);
                    LCD_send_char('0');
                }

            }else{
            //свеху выражение, снизу добавили число
                niz += sym;
                lenn ++;
                for(int8_t i = 0; i<lenn; i++){
                    LCD_set_pos(31-i, 1);
                    LCD_send_char(niz[lenn-1-i]);
                }
            }
        }
    for(int16_t i = 0; i<1000; i++);*/
}
