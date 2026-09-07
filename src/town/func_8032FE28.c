#include "common.h"

extern u8 D_80016000[0x10];

void func_8001A628(s32 unused, s32 arg1, s32 arg2) {
    u8 *base = *(u8 **)D_80016000;

    *(s32 *)(*(u8 **)(base + 0x1C) + 4) = (arg1 << 6) + 0x220;
    *(s32 *)(*(u8 **)(base + 0x1C) + 8) = (arg2 << 6) + 0x220;
}
