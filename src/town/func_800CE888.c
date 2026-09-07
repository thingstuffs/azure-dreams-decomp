#include "common.h"

extern void func_800C2E84(void *arg0, s32 arg2, void *arg3);
extern u8 D_800D6AA8;

void func_800CBFE8(void *arg0, s32 arg1, s32 arg2) {
    func_800C2E84(arg0, arg2, &D_800D6AA8);
    *(u16 *)((u8 *)arg0 + 0x68) += 1;
}
