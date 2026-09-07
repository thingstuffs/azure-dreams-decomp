#include "common.h"

extern s8 func_8009FB34(u8, u8);
extern void func_800A19E4(void *, void *, s32, s32, void *);
extern void func_800A1B44(s32, s32);
extern void func_800AA5CC(void);
extern u8 D_80082E80[];

void func_800AA53C(u8 *arg0) {
    u8 *temp_s0;

    if ((arg0 == 0) || (arg0[0x13] == 0)) {
        temp_s0 = D_80082E80;
        __asm__ __volatile__("" : "=r"(temp_s0) : "0"(temp_s0));
        temp_s0[0x26] = func_8009FB34(temp_s0[0x24], temp_s0[0x25]);
        func_800A1B44(3, 6);
        return;
    }
    temp_s0 = *(u8 **)(arg0 - 0x14);
    temp_s0[0x26] = func_8009FB34(temp_s0[0x24], temp_s0[0x25]);
    func_800A19E4(temp_s0, arg0, 3, 6, arg0 + 0x9C);
}
