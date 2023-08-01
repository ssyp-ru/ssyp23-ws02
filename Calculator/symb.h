#ifndef __SYMB_H__
#define __SYMB_H__

#define PD_ODR (*(volatile char*)0x500F)
#define PD_IDR (*(volatile char*)0x5010)
#define PD_DDR (*(volatile char*)0x5011)
#define PD_CR1 (*(volatile char*)0x5012)
#define PD_CR2 (*(volatile char*)0x5013)

char chemyravno();
char chet(char virag);
#endif
