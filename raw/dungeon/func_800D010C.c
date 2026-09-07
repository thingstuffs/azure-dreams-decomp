#include "common.h"

extern s32 D_800814A0[];
extern void func_800478B8(void *arg);

void func_800D586C(void *arg0, void *unused, void *arg2) {
    u16 temp;

    func_800478B8(arg2);
    temp = *(u16 *)((u8 *)arg2 + 0x14) & 0x6000;
    *(u16 *)((u8 *)arg2 + 0x14) = temp;
    if (temp != 0) {
        *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
        D_800814A0[0] = D_800814A0[0] | 0x8000;
    }
}
