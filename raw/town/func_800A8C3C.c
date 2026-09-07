#include "common.h"

extern struct S_80082EA8 {
    s32 ***p;
    s32 pad[2];
} D_80082EA8;

s32 func_800A639C(s32 arg0) {
    s32 *base = **D_80082EA8.p;
    arg0 = (arg0 << 0x10) >> 0xE;
    arg0 += (s32)base;
    return *(s32 *)arg0;
}
