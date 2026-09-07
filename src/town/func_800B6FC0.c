#include "common.h"

extern void func_800B2D00(s32, void *, s32);

void func_800B4720(s32 arg0, u8 **arg1) {
    u8 *ptr = *arg1;
    func_800B2D00(arg0, ptr + 0x2C, *(s32 *)(ptr + 0x40));
}
