#include <stdint.h>
#include "symb.h"

char chemyravno()
{
    char symb = 0;
    for(uint8_t i = 0; i < 4; i++)
    {
        PD_ODR &= 0b00001111;
        PD_ODR |= ~(1 << (i + 4));
        uint8_t tmp = PD_IDR & 0x0F;
        if (i == 0)
        {
            switch(tmp)
            {
            case 0b1110:
                symb = '1'; //D
                break;
            case 0b1101:
                symb = '4'; //C
                break;
            case 0b1011:
                symb = '7'; //B
                break;
            case 0b0111:
                symb = ' '; //A
                break;
            }
        }   else    if (i==1)
        {
            switch(tmp)
            {
            case 0b1110:
                symb = '2'; //#
                break;
            case 0b1101:
                symb = '5';
                break;
            case 0b1011:
                symb = '8';
                break;
            case 0b0111:
                symb = '0';
                break;
            }
        }   else    if (i==2)
        {
            switch(tmp)
            {
            case 0b1110:
                symb = '3';
                break;
            case 0b1101:
                symb = '6';
                break;
            case 0b1011:
                symb = '9';
                break;
            case 0b0111:
                symb = '=';
                break;
            }
        }   else    if (i==3)
        {
            switch(tmp)
            {
            case 0b1110:
                symb = '+'; //*
                break;
            case 0b1101:
                symb = '-';
                break;
            case 0b1011:
                symb = '*';
                break;
            case 0b0111:
                symb = '/';
                break;
            }
        }

    }
    return symb;
}

char chet(char virag){
    return '0'; //norm chet
}
