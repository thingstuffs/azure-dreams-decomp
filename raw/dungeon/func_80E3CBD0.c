#include "common.h"

extern s32 D_800814A0[];
extern void func_80176478(void) __attribute__((noreturn));

void func_80E3CBD0(void *arg0, s32 *arg1, u8 *arg2)
{
    u16 count;
    u8 value;

    count = *(u16 *)((u8 *)arg0 + 0x20) - 1;
    *(u16 *)((u8 *)arg0 + 0x20) = count;
    if ((s16)count <= 0) {
        *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
        func_80176478();
    }

    value = arg2[0xC];
    value -= value / (s16)count;
    arg2[0xC] = value;
    arg2[0xD] = value;
    arg2[0xE] = value;

    arg1[0] += arg1[3];
    arg1[1] += arg1[4];
    arg1[2] += arg1[5];
    arg1[5] += 0x60000;
}
