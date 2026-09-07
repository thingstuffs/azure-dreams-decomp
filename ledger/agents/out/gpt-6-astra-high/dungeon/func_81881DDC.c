#include "common.h"

extern u16 D_800257CE[5];
extern s32 D_800814A0[3];

__asm__(".set D_800257CE, 0x800257CE");

typedef struct {
    u8 pad[12];
    u8 red;
    u8 green;
    u8 blue;
} EffectColor;

/* Fade the effect color and set completion flags when red falls below eight. */
void func_800255DC(u16 *effect_data, s32 unused, EffectColor *color) {
    u8 red;
    u8 green;
    u8 blue;

    D_800257CE[0]++;

    red = color->red;
    green = color->green;
    color->red = red - (red >> 3);
    blue = color->blue;
    color->green = green - (green >> 3);
    color->blue = blue - (blue >> 3);

    if (color->red < 8) {
        effect_data[-1] |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
