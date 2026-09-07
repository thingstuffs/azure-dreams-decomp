#include "common.h"

typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;

#ifndef NULL
#define NULL 0
#endif

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

typedef s32 M2C_UNK;

extern s32 rand(void);
extern void *func_8009C390(void *, M2C_UNK, s32, s32);
extern void func_8009C46C(void *, void *, void *);
extern u8 D_80088D78[8];
extern M2C_UNK D_800D06C8[3];

void func_8009C648(u8 *arg0, M2C_UNK arg1) {
    s8 sp[6];
    s32 var_s5;
    M2C_UNK *var_s4;
    s32 var_s3;
    void *temp_s0;
    void *temp_s1;
    void *temp_v0;
    void *var_a0;
    s32 temp_rng;
    register void *tail_s0 ASM_REG("$5");
    register void *held_arg0 ASM_REG("$22") = arg0;
    register M2C_UNK held_arg1 ASM_REG("$23") = arg1;

    memcpy(sp, D_80088D78, 6);
    var_s3 = 0;
    var_s5 = 0xFFFC0000;
    ASM_KEEP(var_s5);
    var_s4 = D_800D06C8;
    ASM_KEEP(held_arg0);
    ASM_KEEP(held_arg1);
    var_a0 = (u8 *)held_arg0 - 0x20;
loop_1:
    temp_v0 = func_8009C390(var_a0, held_arg1, M2C_FIELD(var_s4, s32 *, 0), M2C_FIELD(var_s4, s32 *, 4));
    if (temp_v0 != NULL) {
        temp_s0 = M2C_FIELD(temp_v0, void **, 8);
        temp_s1 = (u8 *)temp_v0 + 0x20;
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 0xC), s32 *, 8) =
            ((s32 *)M2C_FIELD(held_arg0, s32 *, 0x80))[sp[var_s3]];
        M2C_FIELD(temp_s1, s32 *, 0x60) = var_s3;
        M2C_FIELD(temp_s0, s32 *, 0xC) = (s32)((rand() * 0x10) + var_s5);
        M2C_FIELD(temp_s0, s32 *, 0x10) = (s32)((rand() * 0x10) + var_s5);
        temp_rng = rand();
        tail_s0 = temp_s0;
        ASM_KEEP(tail_s0);
        var_s4 += 2;
        M2C_FIELD(tail_s0, s32 *, 0x14) = (s32)(0xFFF00000 - (temp_rng * 0x10));
        M2C_FIELD(tail_s0, s32 *, 0) =
            (s32)(M2C_FIELD(tail_s0, s32 *, 0) + (M2C_FIELD(tail_s0, s32 *, 0xC) * 8));
        M2C_FIELD(tail_s0, s32 *, 4) =
            (s32)(M2C_FIELD(tail_s0, s32 *, 4) + (M2C_FIELD(tail_s0, s32 *, 0x10) * 8));
        func_8009C46C(temp_s1, tail_s0, M2C_FIELD(temp_v0, void **, 0xC));
        var_s3 += 1;
        var_a0 = (u8 *)held_arg0 - 0x20;
        if (var_s3 < 6) {
            goto loop_1;
        }
    }
}
