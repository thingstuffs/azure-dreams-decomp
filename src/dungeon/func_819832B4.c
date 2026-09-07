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

void func_80024AB4(u16 *arg0, s32 arg1, EffectColor *arg2) {
    u8 red;
    u8 green;
    u8 blue;

    D_800269F8[0]++;

    red = arg2->red;
    green = arg2->green;
    arg2->red = red - (red >> 2);
    blue = arg2->blue;
    arg2->green = green - (green >> 2);
    arg2->blue = blue - (blue >> 2);

    if (arg2->red < 4) {
        arg0[-1] |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
