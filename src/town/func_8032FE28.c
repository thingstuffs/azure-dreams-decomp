#include "common.h"

extern u8 D_80016000[0x10];

/* Store coordinates scaled by 64 and offset by 0x220. */
void func_8001A628(s32 unused, s32 x, s32 y) {
    u8 *base = *(u8 **)D_80016000;

    *(s32 *)(*(u8 **)(base + 0x1C) + 4) = (x << 6) + 0x220;
    *(s32 *)(*(u8 **)(base + 0x1C) + 8) = (y << 6) + 0x220;
}
