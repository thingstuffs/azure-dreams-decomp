#include "common.h"

extern u8 D_800198A4[24];
extern s32 D_80019B8C[3];

/* Check whether the selected record byte at offset 0x16 is at least two. */
s32 func_805D3A94(void) {
    return D_800198A4[(D_80019B8C[0] * 0x18) + 0x16] >= 2;
}
