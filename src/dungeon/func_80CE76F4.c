#include "common.h"

extern s32 D_800814A0[];

/* Update the effect transform, fade its color, and mark expiration when its timer runs out. */
void func_80170EF4(void *effect, s32 unused, void *visual) {
    u16 transform_value;
    u16 ticks_left;
    s8 intensity;

    transform_value = *(u16 *)((u8 *)visual + 0x1E) + 0x78;
    *(u16 *)((u8 *)visual + 0x1E) = transform_value;
    *(u16 *)((u8 *)visual + 0x1C) = transform_value;
    *(u16 *)((u8 *)visual + 0x1A) += 0x2BC;

    ticks_left = *(u16 *)((u8 *)effect + 0x18) - 1;
    *(u16 *)((u8 *)effect + 0x18) = ticks_left;
    if ((s16)ticks_left < 12) {
        intensity = ((s16)ticks_left << 7) / 12;
        *(s8 *)((u8 *)visual + 0xE) = intensity;
        *(s8 *)((u8 *)visual + 0xD) = intensity;
        *(s8 *)((u8 *)visual + 0xC) = intensity;
    }

    if (*(s16 *)((u8 *)effect + 0x18) <= 0) {
        *(u16 *)((u8 *)effect - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
