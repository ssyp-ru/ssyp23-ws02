/*
    Simple LCD Library by SenyaMD
*/

#include "LCD.h"

void SPI_init(div_t divider)
{

    //Software slave managment - enable
    //Internal slave select - enable
    SPI_CR2 |= (1 << SSM) | (1 << SSI);

    SPI_CR1 |= divider << BR;

    //Master mode
    SPI_CR1 |= 1 << MSTR;
    SPI_CR1 |= 1 << SPE;
}

inline void SPI_wait()
{
    while(!(SPI_SR & (1 << TXE)));
}

void SPI_send(uint8_t data)
{
    SPI_wait();
    SPI_DR = data;
}

void LCD_init(display_t* disp, div_t divider)
{

    //Data/~(Command) pin settings
    *(CONTROL_PORT + DDR_OFFSET) |= 1 << DC;
    *(CONTROL_PORT + CR1_OFFSET) |= 1 << DC;
    *(CONTROL_PORT + CR2_OFFSET) |= 1 << DC;
    *(CONTROL_PORT + ODR_OFFSET) |= 1 << DC;

    //Reset pin settings
    *(CONTROL_PORT + DDR_OFFSET) |= 1 << RST;
    *(CONTROL_PORT + CR1_OFFSET) |= 1 << RST;
    *(CONTROL_PORT + CR2_OFFSET) |= 1 << RST;

    //Display init(1 stage - RST = 1 -> wait > 100 ns -> RST = 0)
    *(CONTROL_PORT + ODR_OFFSET) |= 1 << RST;
    for (uint8_t i = 0; i < 255; i++);
    *(CONTROL_PORT + ODR_OFFSET) &= 1 << RST;

    SPI_init(divider);

    //Chip select settings
    *(CONTROL_PORT + DDR_OFFSET) |= 1 << CS;
    *(CONTROL_PORT + CR1_OFFSET) |= 1 << CS;
    *(CONTROL_PORT + CR2_OFFSET) |= 1 << CS;
    *(CONTROL_PORT + ODR_OFFSET) &= ~(1 << CS);

    LCD_send(disp, 0x21, COMMAND);
    LCD_send(disp, 0x13, COMMAND);
    LCD_send(disp, 0x04, COMMAND);
    LCD_send(disp, 0xB8, COMMAND);
    LCD_send(disp, 0x20, COMMAND);
    LCD_send(disp, 0x0C, COMMAND);
}

void LCD_set_mode(display_t* disp, mode_t mode)
{
    if (disp->mode != mode)
    {
        while(SPI_SR & (1 << BSY));
        disp->mode = mode;
        if (mode == COMMAND)
            *(CONTROL_PORT + ODR_OFFSET) &= ~(1 << DC);
        else
            *(CONTROL_PORT + ODR_OFFSET) |= 1 << DC;
    }
}

void LCD_send(display_t* disp, uint8_t data, mode_t mode)
{
    LCD_set_mode(disp, mode);
    SPI_send(data);
}

void LCD_clear(display_t* disp)
{
    for (uint8_t i = 0; i < 6; i++)
    {
        LCD_send(disp, SET_PAGE | i, COMMAND);
        LCD_send(disp, SET_ADDRESS, COMMAND);
        for (uint8_t j = 0; j < 84; j++)
            LCD_send(disp, 0x00, DATA);
    }
}
