#include "common.h"

extern s32 D_800814A0[3];

/* Fade the primitive color and flag the effect when its countdown expires. */
void func_80173C0C(void *effect, s32 unused, void *primitive)
{
    u16 ticks_left;

    *(u16 *)((u8 *)primitive + 0x1A) += 0x320;
    *(s8 *)((u8 *)primitive + 0x0C) =
        (*(u8 *)((u8 *)effect + 0) * *(s16 *)((u8 *)effect + 0x24)) / 5;
    *(s8 *)((u8 *)primitive + 0x0D) =
        (*(u8 *)((u8 *)effect + 1) * *(s16 *)((u8 *)effect + 0x24)) / 5;
    *(s8 *)((u8 *)primitive + 0x0E) =
        (*(u8 *)((u8 *)effect + 2) * *(s16 *)((u8 *)effect + 0x24)) / 5;

    ticks_left = *(u16 *)((u8 *)effect + 0x24) - 1;
    *(s16 *)((u8 *)effect + 0x24) = ticks_left;
    if ((ticks_left << 16) <= 0) {
        s32 *global_flags = D_800814A0;

        *(u16 *)((u8 *)effect - 2) |= 0x8000;
        *global_flags |= 0x8000;
    }
}
