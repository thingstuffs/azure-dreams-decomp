#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s8 D_800E2468[];
s32 func_800A45D8(s32, s32, s16);
s16 func_800BCB04(s32, s32, s16);

s32 func_800D5F80(void *arg0, void *arg1) {
    s16 temp_v0_2;
    s32 temp_s0;
    s32 temp_s1;
    s16 temp_height;
    s32 temp_raw_height;
    void *temp_table;
    void *temp_a1;

    temp_raw_height = M2C_FIELD(arg0, s16 *, 0xA);
    temp_height = temp_raw_height - 0x20;
    temp_table = D_800E2468;
    temp_a1 = temp_table + ((M2C_FIELD(arg1, u16 *, 0x2A) >> 7) & 0x1C);
    temp_s1 = (M2C_FIELD(arg0, s16 *, 2) + (M2C_FIELD(temp_a1, s16 *, 0) << 6)) & 0xFFFF;
    temp_s0 = (M2C_FIELD(arg0, s16 *, 6) + (M2C_FIELD(temp_a1, s16 *, 2) << 6)) & 0xFFFF;
    if ((func_800A45D8(temp_s1, temp_s0, temp_height) << 0x10) == 0) {
        temp_v0_2 = func_800BCB04(temp_s1, temp_s0, temp_height);
        if (temp_v0_2 < 0x200 &&
            (M2C_FIELD(arg0, s16 *, 0xA) - 0x40) < temp_v0_2) {
            goto fail;
        }
    }
    return 1;
fail:
    return 0;
}
