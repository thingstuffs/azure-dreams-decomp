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

/* Advance the RGB fade toward black and set completion flags when it ends. */
void func_80170E2C(FadeState *fade, s32 unused, FadeOutput *output)
{
    s16 remaining;

    remaining = fade->remaining - 1;
    fade->remaining = remaining;
    output->red = (fade->red * remaining) / fade->divisor;
    output->green = (fade->green * (s16)fade->remaining) / fade->divisor;
    output->blue = (fade->blue * (s16)fade->remaining) / fade->divisor;

    if ((s16)fade->remaining <= 0) {
        *(u16 *)((u8 *)fade - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
