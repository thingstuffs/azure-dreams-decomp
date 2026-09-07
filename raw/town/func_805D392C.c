#include "common.h"

extern u8 D_800198A4[];
extern s32 D_80019B8C;

s32 func_8001792C(void) {
    s32 offset;
    u8 *base;

    base = D_800198A4;
    offset = D_80019B8C * 0x18;
    return *(s32 *)(base + offset + 12);
}
