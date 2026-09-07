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

extern u32 *D_801131EC;

u32 func_8008AF2C(s32 arg0, s32 arg1, s32 arg2) {
    u32 *var_a3;
    u32 *var_t0;
    u32 temp_v1;
    u32 mask_3f;
    u32 mask_7f;

    var_t0 = D_801131EC;
    if (M2C_FIELD(var_t0, s32 *, 4) != 0) {
        mask_3f = 0x3F000000;
        mask_7f = 0x007F0000;
        var_a3 = var_t0 + 1;
loop_2:
        temp_v1 = *var_t0;
        if ((arg0 == ((temp_v1 >> 0x17) & 1)) && (arg1 == ((temp_v1 & mask_3f) >> 0x18)) && (arg2 == ((temp_v1 & mask_7f) >> 0x10))) {
            return *var_a3;
        }
        var_a3 += 2;
        var_t0 += 2;
        if (*var_a3 != 0) {
            goto loop_2;
        }
    } else {
        return 0U;
    }
    return 0U;
}
