#include "common.h"

extern s16 D_800269B4;
extern s32 D_800814A0;

/* Dim the effect's color and flag completion when its countdown expires. */
void func_8196B25C(void *effect, s32 unused, u8 *primitive) {
    u16 ticks_left = *(u16 *)((u8 *)effect + 0x2C);

    D_800269B4 = 1;
    ticks_left -= 1;
    *(u16 *)((u8 *)effect + 0x2C) = ticks_left;

    if (primitive[12] >= 65) {
        primitive[14] = 64;
        primitive[13] = 64;
        primitive[12] = 64;
    }

    if (primitive[12] != 0) {
        s32 shade = primitive[14] - 5;

        primitive[14] = shade;
        primitive[13] = shade;
        primitive[12] = shade;
    }

    if (*(s16 *)((u8 *)effect + 0x2C) <= 0) {
        *(u16 *)((u8 *)effect - 2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
