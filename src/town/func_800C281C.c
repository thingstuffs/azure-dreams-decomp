#include "common.h"

extern int func_800478B8(void *arg);
extern int D_800814A0;

void func_800BFF7C(void *arg0, void *unused, void *arg2) {
    func_800478B8(arg2);
    *(s32 *)((s8 *)arg2 + 0xC) += 0xFFEFEFF0;
    if (*(u16 *)((s8 *)arg2 + 0x14) & 0x6000) {
        *(u16 *)((s8 *)arg0 - 2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
