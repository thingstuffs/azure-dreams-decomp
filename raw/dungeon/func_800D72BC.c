#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;
typedef s8 M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern u8 D_800E2954;
extern u8 D_800E2960[];

s32 func_800DCA1C(s32 arg0, s32 arg1) {
    s32 var_a2;
    u8 *var_a1;
    u8 *var_v1;
    u8 temp_v1;

    var_a2 = 0;
    if (arg1 != 0) {
        var_v1 = D_800E2960;
    } else {
        var_v1 = &D_800E2954;
    }
    if (*var_v1 < 9U) {
        var_a1 = var_v1;
        do {
            M2C_FIELD(((*var_a1 * 0x10) + arg0), s32 *, 0xC) = var_a2;
            temp_v1 = *var_a1;
            var_a1 += 1;
            var_a2 = arg0 + (temp_v1 * 0x10);
        } while ((u8) *var_a1 < 9U);
    }
    return var_a2;
}
