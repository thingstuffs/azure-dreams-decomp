#include "common.h"

s32 func_80096A5C(void *arg0, s32 arg1, s32 arg2) {
    u8 *p0 = *(u8 **)((u8 *)arg0 + 0x28);
    u8 *p1 = *(u8 **)p0;
    u8 *p2 = *(u8 **)p1;
    u8 *p3 = *(u8 **)(((s32)(arg1 << 0x10) >> 0xE) + (s32)p2);
    return *(s32 *)(p3 + ((s32)(arg2 << 0x10) >> 0xD) + 4);
}
