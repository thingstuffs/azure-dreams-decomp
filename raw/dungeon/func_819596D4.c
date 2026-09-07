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

extern s16 D_80083780[];
extern u8 D_80083498[];
extern u8 D_800DF334[];
M2C_UNK func_80024654();
void *func_8003FD64();
s32 func_800644B8();
s32 func_80064584();
s16 func_800A07D0();
M2C_UNK func_800B835C();
extern M2C_UNK D_80028214;
extern M2C_UNK D_80024728;

void *func_80024ED4(void *arg0) {
    s32 sp20[2];
    s32 var_s3;
    M2C_UNK var_a0;
    s16 temp_s6;
    u16 temp_v0_2;
    u16 temp_v0_3;
    u16 temp_v0_4;
    u8 *var_a1;
    void *temp_s0;
    void *temp_s1;
    void *temp_v0;
    void *temp_v1;
    void *var_s4;
    s16 *temp_v0_1;

    temp_v0_1 = D_80083780;
    var_s4 = NULL;
    var_s3 = 0;
    temp_s6 = func_800A07D0(temp_v0_1[1], temp_v0_1[3], M2C_FIELD(arg0, s16 *, 2), M2C_FIELD(arg0, s16 *, 6));
    do {
        var_a0 = 0x12;
        if (var_s3 != 0) {
            var_a0 = 0x212;
        }
        var_a1 = var_s4;
        if (var_s4 == NULL) {
            var_a1 = D_80083498;
        }
        temp_v0 = func_8003FD64(var_a0, var_a1);
        temp_s1 = temp_v0 + 0x20;
        if (temp_v0 != NULL) {
            temp_s0 = M2C_FIELD(temp_v0, void **, 8);
            M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_80024728;
            temp_v0_2 = (u16) M2C_FIELD(arg0, s16 *, 2);
            M2C_FIELD(temp_s0, u16 *, 2) = temp_v0_2;
            M2C_FIELD(temp_s0, u16 *, 0xE) = temp_v0_2;
            temp_v0_3 = (u16) M2C_FIELD(arg0, s16 *, 6);
            M2C_FIELD(temp_s0, u16 *, 6) = temp_v0_3;
            M2C_FIELD(temp_s0, u16 *, 0x12) = temp_v0_3;
            temp_v0_4 = M2C_FIELD(arg0, u16 *, 0xA);
            M2C_FIELD(temp_s0, u16 *, 0xA) = temp_v0_4;
            M2C_FIELD(temp_s0, u16 *, 0x16) = temp_v0_4;
            temp_v1 = M2C_FIELD(temp_v0, void **, 0xC);
            M2C_FIELD(temp_v1, M2C_UNK **, 8) = &D_80028214;
            M2C_FIELD(temp_v1, s16 *, 0x1E) = 0x800;
            M2C_FIELD(temp_v1, s16 *, 0x1C) = 0x800;
            M2C_FIELD(temp_s1, s16 *, 0x30) = 0x10;
            if (var_s3 == 0) {
                M2C_FIELD(temp_s1, s16 *, 0x14) = (s16) (M2C_FIELD(temp_s0, u16 *, 2) + (func_80064584(temp_s6) >> 5));
                M2C_FIELD(temp_s1, s16 *, 0x16) = (s16) (M2C_FIELD(temp_s0, u16 *, 6) + (func_800644B8(temp_s6) >> 5));
                M2C_FIELD(temp_s1, s16 *, 0x18) = (s16) (M2C_FIELD(temp_s0, u16 *, 0xA) - 0x40);
                func_80024654((s16) M2C_FIELD(temp_s0, u16 *, 2), (s16) M2C_FIELD(temp_s0, u16 *, 6), (s16) M2C_FIELD(temp_s0, u16 *, 0xA), M2C_FIELD(temp_s1, s16 *, 0x14), (s32) M2C_FIELD(temp_s1, s16 *, 0x16), (s32) M2C_FIELD(temp_s1, s16 *, 0x18), temp_v0 + 0x2C);
                sp20[0] = 0x01200340;
                sp20[1] = 0x200020;
                func_800B835C(D_800DF334, sp20, 1, 0);
            }
            M2C_FIELD(temp_s1, s32 *, 8) = var_s4;
            var_s4 = temp_v0;
            M2C_FIELD(temp_s1, s16 *, 0x38) = var_s3;
        } else {
            return var_s4;
        }
        var_s3++;
    } while (var_s3 < 0x10);
    return temp_v0;
}
