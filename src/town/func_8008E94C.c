#include "common.h"

typedef struct S_8008E94C_Sub {
    s32 f0;
    u8 pad4[0x10];
    s16 shift;
    u16 pad16;
    u16 mask1;
    u16 mask2;
} S_8008E94C_Sub;

typedef struct S_80083160_View {
    u8 pad0[0x1DC];
    S_8008E94C_Sub sub;
} S_80083160_View;

extern S_80083160_View D_80083160;

s32 func_8008C0AC(s32 arg0, s32 arg1)
{
    S_80083160_View *base = &D_80083160;
    S_8008E94C_Sub *p = &base->sub;
    s32 sum;

    sum = (p->mask1 & arg0) + ((s16)(p->mask2 & arg1) << p->shift);
    return base->sub.f0 + ((sum << 0x10) >> 0xF);
}
