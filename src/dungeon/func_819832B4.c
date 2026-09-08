#include "common.h"

extern u16 D_800269F8[5];
extern s32 D_800814A0[3];

__asm__(".set D_800269F8, 0x800269F8");

typedef struct {
    u8 pad[12];
    u8 red;
    u8 green;
    u8 blue;
} EffectColor;

/* Fade the effect color and set flags when red falls below four. */
void func_80024AB4(u16 *effect_data, s32 unused, EffectColor *color) {
    u8 red;
    u8 green;
    u8 blue;

    D_800269F8[0]++;

    red = color->red;
    green = color->green;
    color->red = red - (red >> 2);
    blue = color->blue;
    color->green = green - (green >> 2);
    color->blue = blue - (blue >> 2);

    if (color->red < 4) {
        effect_data[-1] |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
