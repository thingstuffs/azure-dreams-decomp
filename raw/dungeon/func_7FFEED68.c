#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;
typedef s8  M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 func_8008CFB4(s32 *);

s16 func_8008C4C8(void *arg0, s32 arg1, s32 arg2) {
    s32 sp[5];
    s32 temp_v0;
    s32 temp_a2;
    s32 temp_v1;
    s32 var_v0_2;
    void *temp_s0;

    temp_a2 = arg2 * 0x10;
    temp_s0 = temp_a2 + arg1;
    sp[0] = M2C_FIELD(arg0, s32 *, 0) + M2C_FIELD(temp_s0, s32 *, 0);
    sp[1] = M2C_FIELD(arg0, s32 *, 4) + M2C_FIELD(temp_s0, s32 *, 4);
    sp[2] = M2C_FIELD(arg0, s32 *, 8) + M2C_FIELD(temp_s0, s32 *, 8);
    temp_v0 = func_8008CFB4(sp);
    if ((s16) temp_v0 == 0x7FFF) {
        return 0x7FFF;
    }
    temp_v1 = M2C_FIELD(temp_s0, s32 *, 0);
    var_v0_2 = temp_v1 >> 0x10;
    if (temp_v1 < 0) {
        temp_v1 += 0xFFFF;
        var_v0_2 = temp_v1 >> 0x10;
    }
    return temp_v0 - var_v0_2;
}
