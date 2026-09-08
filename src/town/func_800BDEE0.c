#include "common.h"

extern void func_800BB508(s32, s32);

void func_800BB640(s32 arg0, s32 arg1, void *arg2) {
    volatile u16 *field = (volatile u16 *)((u8 *)arg2 + 0x1A);

    func_800BB508(arg0, arg1);
    *field = (u16)(*field + 0x20);
    *field = (u16)(*field & 0xFFF);
}
