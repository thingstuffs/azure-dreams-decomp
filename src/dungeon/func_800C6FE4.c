#include "common.h"

#define U8(p, o)  (*(u8  *)((u8 *)(p) + (o)))
#define S16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U16(p, o) (*(u16 *)((u8 *)(p) + (o)))

extern s32 D_800814A0;

/* Fade the color toward 0xE0, then to black, and flag completion. */
void func_800CC744(void *fade, void *unused, void *color) {
    s16 steps;
    s16 brighten_left;
    s16 darken_left;
    s32 blue_step;
    u8 blue;
    u8 red;
    u8 green;

    if (S16(fade, 0) == 0) {
        red = U8(color, 0xC);
        U8(color, 0xC) = red + ((0xE0 - red) / S16(fade, 2));
        green = U8(color, 0xD);
        steps = S16(fade, 2);
        blue = U8(color, 0xE);
        U8(color, 0xD) = green + ((0xE0 - green) / steps);
        blue_step = (0xE0 - blue) / S16(fade, 2);
        U8(color, 0xE) = blue + blue_step;
        brighten_left = U16(fade, 2) - 1;
        S16(fade, 2) = brighten_left;
        if ((brighten_left << 16) <= 0) {
            S16(fade, 2) = 0x10;
            U16(fade, 0)++;
            return;
        }
    } else {
        U8(color, 0xC) = U8(color, 0xC) - (U8(color, 0xC) / S16(fade, 2));
        U8(color, 0xD) = U8(color, 0xD) - (U8(color, 0xD) / S16(fade, 2));
        U8(color, 0xE) = U8(color, 0xE) - (U8(color, 0xE) / S16(fade, 2));
        darken_left = U16(fade, 2) - 1;
        S16(fade, 2) = darken_left;
        if ((darken_left << 16) <= 0) {
            U16(fade, -2) |= 0x8000;
            D_800814A0 |= 0x8000;
        }
    }
}
