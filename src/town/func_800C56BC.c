#include "common.h"

/* D_80083160: shared state table (own view here); only the s16 field at
 * +0xC8 is read via this view. */
struct S_800C56BC {
    char pad0[0xC8];
    s16 unkC8;
};

extern struct S_800C56BC D_80083160;

s32 func_800C2E1C(s32 arg0, s16 arg1)
{
    struct S_800C56BC *base = &D_80083160;
    s16 var_v1;
    s32 temp_lo;
    s32 val;

    var_v1 = arg1;
    if (arg1 == 0) {
        var_v1 = 1;
    }
    temp_lo = 0x1000 / var_v1;
    val = base->unkC8 + (s16) temp_lo / 2;
    val += 0x400;
    val -= arg0;
    return (s32) (val & 0xFFF) / (s16) temp_lo;
}
