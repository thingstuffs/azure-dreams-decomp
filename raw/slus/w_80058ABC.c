#include "common.h"

/* Calls func_800589B8(a0) four times and packs the four byte-masked results into a 32-bit word via func_80058A7C. */
extern s32 func_800589B8(s32 a0);
extern u32 func_80058A7C(s32 a0, s32 a1, s32 a2, s32 a3);

u32 func_80058ABC(s32 a0)
{
    s32 b0, b1, b2, b3;

    b0 = func_800589B8(a0);
    b1 = func_800589B8(a0);
    b2 = func_800589B8(a0);
    b3 = func_800589B8(a0);
    return func_80058A7C(b0 & 0xFF, b1 & 0xFF, b2 & 0xFF, b3 & 0xFF);
}
