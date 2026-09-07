#include "common.h"

extern void *D_80174CE0[];
extern s32 D_800814A0[3];
extern void func_800A32A4(void *arg0);

void func_80170C3C(void) {
    void *s0;

    s0 = D_80174CE0[0];
    if (s0 != 0) {
        s0 = (u8 *)s0 + 0x20;
        func_800A32A4(s0);
        *(u16 *)((u8 *)s0 - 2) |= 0x8000;
        D_80174CE0[0] = 0;
        D_800814A0[0] |= 0x8000;
    }
}
