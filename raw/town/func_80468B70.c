#include "common.h"

extern u8 D_80016000[0x10];

void func_80019B70(s16 *arg0) {
    {
        s32 *p = *(s32 **)((u8 *)*(s32 **)D_80016000 + 0x1C);
        p[0] = arg0[0];
    }
    {
        s32 *base = *(s32 **)D_80016000;
        ((s32 *)*(s32 **)((u8 *)base + 0x1C))[1] = arg0[1];
        ((s32 *)*(s32 **)((u8 *)base + 0x1C))[2] = arg0[2];
    }
}
