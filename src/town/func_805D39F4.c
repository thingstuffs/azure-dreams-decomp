#include "common.h"

extern u8 D_800198A4[];
extern s32 D_80019B8C;
extern s32 D_80019A70[];

s32 func_805D39F4(void) {
    u8 idx;

    idx = D_800198A4[(D_80019B8C * 0x18) + 0x16];
    return D_80019A70[idx];
}
