#include "common.h"

extern s16 D_80025384;
extern s32 D_800814A0;

/* Fade the primitive and flag the effect when its countdown expires. */
void func_800244F0(void *effect, s32 unused, u8 *primitive) {
    u16 ticks_left = *(u16 *)((u8 *)effect + 0x2A);

    D_80025384 = 1;
    ticks_left -= 1;
    *(u16 *)((u8 *)effect + 0x2A) = ticks_left;

    if (primitive[12] >= 65) {
        primitive[14] = 64;
        primitive[13] = 64;
        primitive[12] = 64;
    }

    if (primitive[12] != 0) {
        s32 brightness = primitive[14] - 5;

        primitive[14] = brightness;
        primitive[13] = brightness;
        primitive[12] = brightness;
    }

    if (*(s16 *)((u8 *)effect + 0x2A) <= 0) {
        *(u16 *)((u8 *)effect - 2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
