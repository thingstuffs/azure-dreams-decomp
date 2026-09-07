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

void func_800255DC(u16 *arg0, s32 arg1, EffectColor *arg2) {
    u8 red;
    u8 green;
    u8 blue;

    D_800257CE[0]++;

    red = arg2->red;
    green = arg2->green;
    arg2->red = red - (red >> 3);
    blue = arg2->blue;
    arg2->green = green - (green >> 3);
    arg2->blue = blue - (blue >> 3);

    if (arg2->red < 8) {
        arg0[-1] |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
