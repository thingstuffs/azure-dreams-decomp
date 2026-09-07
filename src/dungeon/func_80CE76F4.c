#include "common.h"

extern s32 D_800814A0[];

void func_80170EF4(void *arg0, s32 arg1, void *arg2) {
    u16 value;
    u16 timer;
    s8 shade;

    value = *(u16 *)((u8 *)arg2 + 0x1E) + 0x78;
    *(u16 *)((u8 *)arg2 + 0x1E) = value;
    *(u16 *)((u8 *)arg2 + 0x1C) = value;
    *(u16 *)((u8 *)arg2 + 0x1A) += 0x2BC;

    timer = *(u16 *)((u8 *)arg0 + 0x18) - 1;
    *(u16 *)((u8 *)arg0 + 0x18) = timer;
    if ((s16)timer < 12) {
        shade = ((s16)timer << 7) / 12;
        *(s8 *)((u8 *)arg2 + 0xE) = shade;
        *(s8 *)((u8 *)arg2 + 0xD) = shade;
        *(s8 *)((u8 *)arg2 + 0xC) = shade;
    }

    if (*(s16 *)((u8 *)arg0 + 0x18) <= 0) {
        *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
