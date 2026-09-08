#include "common.h"

extern s16 D_800261B0;
extern s32 D_800814A0;

/* Advance the effect fade and mark it finished when its countdown expires. */
void func_819A133C(void *effect, s32 unused, void *primitive)
{
    s32 intensity;
    u16 ticks_left;

    ticks_left = *(u16 *)((u8 *)effect + 0x3A) - 1;
    intensity = ((s32)(ticks_left << 16) >> 9) /
            *(s16 *)((u8 *)effect + 0x3C);
    D_800261B0 = 1;
    *(u16 *)((u8 *)effect + 0x3A) = ticks_left;
    *(s8 *)((u8 *)primitive + 0x0E) = intensity;
    *(s8 *)((u8 *)primitive + 0x0D) = intensity;
    *(s8 *)((u8 *)primitive + 0x0C) = intensity;
    *(u8 *)((u8 *)effect + 0x8C) -= 1;
    *(u16 *)((u8 *)primitive + 0x1A) += *(u16 *)((u8 *)effect + 0x40);
    if (*(s16 *)((u8 *)effect + 0x3A) <= 0) {
        *(u16 *)((u8 *)effect - 2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
