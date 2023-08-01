#ifndef __PTR_H__
#define __PTR_H__

#include <stdint.h>

#define TILE_SIZE 8

#define RANDOM_TABLE (volatile uint8_t*)0x4000
#define RANDOM_TABLE_SIZE 64

#define P1_TABLE (volatile uint8_t*)0x4040

#define P2_TABLE (volatile uint8_t*)0x4048

#define E2_TABLE (volatile uint8_t*)0x4050

#define BOX_TABLE (volatile uint8_t*)0x4058

#define E1_TABLE (volatile uint8_t*)0x4060

#endif
