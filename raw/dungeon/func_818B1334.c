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

extern void func_80024610(void *, void *, void *, s32, s32, M2C_UNK *, s32, s32);
extern s32 func_800644B8();
extern s32 func_80064584();

s32 func_818B1334(void *arg0, void *arg1, void *arg2) {
    M2C_UNK sp20[34];
    M2C_UNK *var_s2;
    register M2C_UNK *var_s5;
    s16 temp_s0_2;
    s32 temp_a1;
    s32 temp_s0;
    s32 temp_v0;
    s32 var_a0;
    s32 var_s0;
    s32 var_s1;
    s32 var_s1_2;
    u16 temp_a2;
    void *var_s2_2;
    register void *call_a0 ASM_REG("$4");

    var_s5 = sp20;
    var_s1 = 0x10;
    var_s2 = var_s5 + 16;
    do {
        var_s0 = var_s1;
        if (var_s1 < 0) {
            var_s0 = var_s1 + 0xF;
        }
        temp_s0 = (var_s1 - ((var_s0 >> 4) * 0x10)) << 8;
        M2C_FIELD(var_s2, s32 *, 0) = (s32) (func_800644B8(temp_s0) >> 4);
        M2C_FIELD(var_s2, s32 *, 0x44) = (s32) (func_80064584(temp_s0) >> 4);
        var_s2 -= 1;
    } while (--var_s1 >= 0);
    var_s1_2 = 0;
    var_s2_2 = arg0;
    do {
        temp_v0 = M2C_FIELD(arg0, s16 *, 0x10) - var_s1_2;
        var_a0 = temp_v0;
        if (temp_v0 < 0) {
            var_a0 = temp_v0 + 0xF;
        }
        temp_s0_2 = (func_800644B8((temp_v0 - ((var_a0 >> 4) * 0x10)) << 9) >> 9) + 0x20;
        func_80064584(var_s1_2 << 0xA);
        call_a0 = arg0;
        ASM_KEEP(call_a0);
        temp_a2 = M2C_FIELD(var_s2_2, u16 *, 0x1A);
        var_s2_2 += 2;
        temp_a1 = var_s1_2 << 0x11;
        var_s1_2 += 1;
        func_80024610(call_a0, arg1, arg2, temp_s0_2, (s32) (s16) (M2C_FIELD(arg1, u16 *, 0xA) - temp_a2), var_s5, 0xFF, temp_a1 >> 0x10);
    } while (var_s1_2 < 8);
    return 0;
}
