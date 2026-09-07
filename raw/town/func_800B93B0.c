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

M2C_UNK func_8004B1A4();
M2C_UNK func_8004E99C();
M2C_UNK func_800B6B78();

void func_800B6B10(void **arg0) {
    s32 var_s1;
    s32 var_s2;
    u8 temp_v1;
    void **var_s0;
    void *temp_a0;

    var_s1 = 0;
    var_s2 = 2;
    var_s0 = arg0;
loop_1:
    temp_a0 = *var_s0;
    temp_v1 = M2C_FIELD(M2C_FIELD(temp_a0, void **, 4), u8 *, 0xE);
    if (temp_v1 == var_s2) {
        func_8004E99C(M2C_FIELD(temp_a0, s32 *, 0));
        func_800B6B78();
        return;
    }
    if (temp_v1 == 1) {
        func_8004B1A4(M2C_FIELD(temp_a0, s32 *, 0));
        M2C_FIELD(*var_s0, s32 *, 0) = 0;
        M2C_FIELD(M2C_FIELD(*var_s0, void **, 4), s8 *, 0xE) = 0;
    }
    var_s1 += 1;
    var_s0 = (void **)((s8 *)((void **)((s8 *)var_s0 + 4)));
    if (var_s1 >= 0x18) {
        return;
    }
    goto loop_1;
}
