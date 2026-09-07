#include "common.h"

#define FIELD(expr, type, offset) (*(type)((s8 *)(expr) + (offset)))

extern s16 D_800261B0;
extern s32 D_800814A0;

void func_819A0FC0(void *arg0, void *unused, void *arg2)
{
    s32 temp_lo;
    u16 temp_a0;

    temp_a0 = FIELD(arg0, u16 *, 0x3A) - 1;
    temp_lo = (s32)((s32)(temp_a0 << 0x10) >> 9) /
              (s16)FIELD(arg0, s16 *, 0x3C);
    D_800261B0 = 1;
    FIELD(arg0, u16 *, 0x3A) = temp_a0;
    FIELD(arg2, s8 *, 0xE) = (s8)temp_lo;
    FIELD(arg2, s8 *, 0xD) = (s8)temp_lo;
    FIELD(arg2, s8 *, 0xC) = (s8)temp_lo;
    if ((s16)FIELD(arg0, u16 *, 0x3A) <= 0) {
        FIELD(arg0, u16 *, -2) =
            (u16)(FIELD(arg0, u16 *, -2) | 0x8000);
        D_800814A0 |= 0x8000;
    }
}
