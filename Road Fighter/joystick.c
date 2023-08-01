#include "joystick.h"
#include <stdint.h>

void joystick_init(void)
{
    ADC_CR1 |= (1 << 0);
    PA_DDR &= ~(1 << 0);
    PA_CR1 |= 1 << 1;
    PA_CR1 |= 1 << 2;
//ADC_CR2 =
//ADC_CSR =

}

uint8_t joystick_state()
{
    uint8_t state = 0b00000000;
    uint16_t x = 0;
    uint16_t y = 0;

    if (PA_IDR & 0b00000100)
    {
        state |= 0b00000010;
    }


    if (PA_IDR & 0b00000010)
    {
        state |= 0b00000001;
    }

    ADC_CSR &= ~(1 << 7);
    ADC_CR1 |= 1;
    while (!(ADC_CSR & (1 << 7)));
    x = ADC_DRH;
    x <<= 2;
    x |= ADC_DRL;
    ADC_CSR &= ~3;
    ADC_CSR |= 4;

    ADC_CSR &= ~(1 << 7);
    ADC_CR1 |= 1;
    while (!(ADC_CSR & (1 << 7)));
    y = ADC_DRH;
    y <<= 2;
    y |= ADC_DRL;
    ADC_CSR &= ~4;
    ADC_CSR |= 3;
    ADC_CSR &= ~(1 << 7);

    if (y > 600)
    {
        state |= (1 << 4);
    }

    if (y < 400)
    {
        state |= (1 << 5);
    }

    if (x > 800)
    {
        state |= (1 << 2);
    }

    if (x < 200)
    {
        state |= (1 << 3);
    }

    return state;
}
