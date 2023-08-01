#include "sprite.h"
#include "field.h"

int8_t ad, pg, sh;

void erase_sprite(display_t* display, sprite_t* sprite, uint8_t x, uint8_t y) {
    ad = x - sprite->cx, pg = (y - sprite->cy) / 8, sh = (y - sprite->cy) % 8;
    for (int i = 0; i < 8; ++i)
        if (sprite->en & (1 << i))
            draw(display, pg, ad + i, 0);
    if (sh)
        for (int i = 0; i < 8; ++i)
            if (sprite->en & (1 << i))
                draw(display, pg + 1, ad + i, 0);
}

void draw_sprite(display_t* display, sprite_t* sprite, uint8_t x, uint8_t y) {
    ad = x - sprite->cx, pg = (y - sprite->cy) / 8, sh = (y - sprite->cy) % 8;
    for (int i = 0; i < 8; ++i)
        if (sprite->en & (1 << i))
            draw(display, pg, ad + i, sprite->arr[i] << sh);
    if (sh)
        for (int i = 0; i < 8; ++i)
            if (sprite->en & (1 << i))
                draw(display, pg + 1, ad + i, sprite->arr[i] >> (8 - sh));
}
