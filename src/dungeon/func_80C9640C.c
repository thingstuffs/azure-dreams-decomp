#include "common.h"

extern s32 D_800814A0[3];

void func_80173C0C(void *arg0, s32 arg1, void *arg2)
{
    u16 value;

    *(u16 *)((u8 *)arg2 + 0x1A) += 0x320;
    *(s8 *)((u8 *)arg2 + 0x0C) =
        (*(u8 *)((u8 *)arg0 + 0) * *(s16 *)((u8 *)arg0 + 0x24)) / 5;
    *(s8 *)((u8 *)arg2 + 0x0D) =
        (*(u8 *)((u8 *)arg0 + 1) * *(s16 *)((u8 *)arg0 + 0x24)) / 5;
    *(s8 *)((u8 *)arg2 + 0x0E) =
        (*(u8 *)((u8 *)arg0 + 2) * *(s16 *)((u8 *)arg0 + 0x24)) / 5;

    value = *(u16 *)((u8 *)arg0 + 0x24) - 1;
    *(s16 *)((u8 *)arg0 + 0x24) = value;
    if ((value << 16) <= 0) {
        s32 *flags = D_800814A0;

        *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
        *flags |= 0x8000;
    }
}
