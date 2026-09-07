#include "common.h"

extern s16 D_800267B8[5];
extern s32 D_800814A0[3];

void func_800252E4(u8 *arg0, void *arg1, u8 *arg2)
{
    u8 *object;
    u8 *other;
    s16 timer;
    s32 intensity;
    s32 global_flags;
    u16 other_flags;

    object = *(u8 **)(arg0 + 0x3C);
    D_800267B8[0] = 1;
    if ((u32)(object[0x13] - 0x33) < 4U) {
        *(u16 *)(arg0 - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
        return;
    }

    *(u16 *)(arg0 + 2) -= 1;
    other = *(u8 **)(*(u8 **)(arg0 + 0x3C) - 0x14);
    *(u16 *)(arg2 + 0x14) &= 0xFF7F;
    *(u16 *)(other + 0x14) |= 0x80;

    timer = *(s16 *)(arg0 + 2);
    if (timer < 20) {
        intensity = ((20 - timer) * 96) / 20 + 32;
        arg2[0xC] = intensity;
        arg2[0xD] = intensity;
        arg2[0xE] = intensity;
    } else if (timer < 40) {
        intensity = ((timer - 20) * 96) / 20 + 32;
        arg2[0xC] = intensity;
        arg2[0xD] = intensity;
        arg2[0xE] = intensity;
    }

    if (*(s16 *)(arg0 + 2) <= 0) {
        *(u16 *)(arg0 - 2) |= 0x8000;
        global_flags = D_800814A0[0];
        other_flags = *(u16 *)(other + 0x14);
        global_flags |= 0x8000;
        other_flags &= 0xFF7F;
        D_800814A0[0] = global_flags;
        *(u16 *)(other + 0x14) = other_flags;
    }
}
