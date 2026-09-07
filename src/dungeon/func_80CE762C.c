#include "common.h"

extern s32 D_800814A0[3];

typedef struct {
    u8 red;
    u8 green;
    u8 blue;
    u8 pad_03[0x15];
    u16 remaining;
    s16 divisor;
} FadeState;

typedef struct {
    u8 pad_00[0xC];
    s8 red;
    s8 green;
    s8 blue;
} FadeOutput;

void func_80170E2C(FadeState *arg0, s32 arg1, FadeOutput *arg2)
{
    s16 remaining;

    remaining = arg0->remaining - 1;
    arg0->remaining = remaining;
    arg2->red = (arg0->red * remaining) / arg0->divisor;
    arg2->green = (arg0->green * (s16)arg0->remaining) / arg0->divisor;
    arg2->blue = (arg0->blue * (s16)arg0->remaining) / arg0->divisor;

    if ((s16)arg0->remaining <= 0) {
        *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
