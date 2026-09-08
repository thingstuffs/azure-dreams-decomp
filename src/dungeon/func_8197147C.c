#include "common.h"

extern s16 D_80025FF4;
extern s32 D_800814A0;

/* Advance an effect's fade and mark it finished when its countdown expires. */
void func_8197147C(void *effect, s32 unused, void *packet)
{
    s32 intensity;
    u16 ticks_left;

    ticks_left = *(u16 *)((u8 *)effect + 0x38) - 1;
    intensity = ((s32)(ticks_left << 16) >> 9) /
            *(s16 *)((u8 *)effect + 0x3A);
    D_80025FF4 = 1;
    *(u16 *)((u8 *)effect + 0x38) = ticks_left;
    *(s8 *)((u8 *)packet + 0x0E) = intensity;
    *(s8 *)((u8 *)packet + 0x0D) = intensity;
    *(s8 *)((u8 *)packet + 0x0C) = intensity;
    *(u8 *)((u8 *)effect + 0x84) -= 1;
    *(u16 *)((u8 *)packet + 0x1A) += *(u16 *)((u8 *)effect + 0x44);
    if (*(s16 *)((u8 *)effect + 0x38) <= 0) {
        *(u16 *)((u8 *)effect - 2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
