#include "common.h"

extern void func_800478B8(void *arg0);
extern s32 D_800814A0[3];

void func_800BF15C(void *arg0, s32 arg1, void *arg2)
{
    func_800478B8(arg2);
    if (*(u16 *)((u8 *)arg2 + 0x14) & 0x6000) {
        *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
