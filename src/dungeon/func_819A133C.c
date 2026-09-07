#include "common.h"

extern s16 D_800261B0;
extern s32 D_800814A0;

void func_819A133C(void *arg0, s32 arg1, void *arg2)
{
    s32 value;
    u16 count;

    count = *(u16 *)((u8 *)arg0 + 0x3A) - 1;
    value = ((s32)(count << 16) >> 9) /
            *(s16 *)((u8 *)arg0 + 0x3C);
    D_800261B0 = 1;
    *(u16 *)((u8 *)arg0 + 0x3A) = count;
    *(s8 *)((u8 *)arg2 + 0x0E) = value;
    *(s8 *)((u8 *)arg2 + 0x0D) = value;
    *(s8 *)((u8 *)arg2 + 0x0C) = value;
    *(u8 *)((u8 *)arg0 + 0x8C) -= 1;
    *(u16 *)((u8 *)arg2 + 0x1A) += *(u16 *)((u8 *)arg0 + 0x40);
    if (*(s16 *)((u8 *)arg0 + 0x3A) <= 0) {
        *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
