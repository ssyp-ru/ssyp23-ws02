#ifndef LCD_H_INCLUDED
#define LCD_H_INCLUDED

#include <stdint.h>

#define SPI_CR1 (*(volatile uint8_t*)0x5200)
#define SPI_CR2 (*(volatile uint8_t*)0x5201)
#define SPI_ICR (*(volatile uint8_t*)0x5202)
#define SPI_SR (*(volatile uint8_t*)0x5203)
#define SPI_DR (*(volatile uint8_t*)0x5204)
#define SPI_CRCPR (*(volatile uint8_t*)0x5205)
#define SPI_RXCRCR (*(volatile uint8_t*)0x5206)
#define SPI_TXCRCR (*(volatile uint8_t*)0x5207)

#define CONTROL_PORT (volatile uint8_t*)0x500A
#define ODR_OFFSET      0
#define IDR_OFFSET      1
#define DDR_OFFSET      2
#define CR1_OFFSET      3
#define CR2_OFFSET      4

#define CS              2
#define DC              4
#define RST             3
#define MOSI            6
#define SCK             5

#define SPE             6
#define BR              3
#define MSTR            2

#define SSM             1
#define SSI             0

#define TXE             1
#define MODF            5
#define BSY             7

#define SET_PAGE        0x40
#define SET_ADDRESS     0x80

typedef enum
{
    COMMAND,
    DATA
} mode_t;

typedef enum
{
    DIV_2,
    DIV_4,
    DIV_8,
    DIV_16,
    DIV_32,
    DIV_64,
    DIV_128,
    DIV_256,
} div_t;

typedef struct
{
    mode_t mode;
    div_t divider;
} display_t;

void LCD_init(display_t* disp, div_t divider);

void LCD_set_mode(display_t* disp, mode_t mode);

void LCD_send(display_t* disp, uint8_t data, mode_t mode);

void LCD_clear(display_t* disp);

#endif // LCD_H_INCLUDED
