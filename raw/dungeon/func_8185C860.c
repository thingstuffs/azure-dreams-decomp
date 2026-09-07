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

extern u8 *D_800E3D7C[];
s32 func_800A2CB8();
s32 func_800A41F0();
s32 func_800A6D30();
M2C_UNK func_800C87C4();
extern u8 D_800E0003[];
extern u8 D_800E3D68;

void func_8185C860(s16 arg0, s16 arg1, M2C_UNK arg2, s32 arg3) {
    M2C_UNK var_a1;
    s16 var_s1;
    s32 temp_a2;
    s32 var_v0_2;
    s32 var_v0_3;
    u8 *var_s0;
    void *temp_v1;

    var_s0 = *D_800E3D7C;
    var_s1 = (s16)(((u32)(arg3 & 0xFF) >> 2) + 0x10);
    do {
        if ((func_800A2CB8(arg2, var_s0) << 0x10) != 0) {
            temp_v1 = M2C_FIELD(var_s0, void **, -0x14);
            var_v0_2 = M2C_FIELD(temp_v1, u8 *, 0x24) - arg0;
            if (var_v0_2 < 0) {
                var_v0_2 = 0 - var_v0_2;
            }
            if (var_v0_2 < 3) {
                var_v0_3 = M2C_FIELD(temp_v1, u8 *, 0x25) - arg1;
                if (var_v0_3 < 0) {
                    var_v0_3 = 0 - var_v0_3;
                }
                if (var_v0_3 < 3) {
                    if ((func_800A41F0(var_s0) << 0x10) != 0) {
                        temp_a2 = var_s1 + (func_800A6D30() & 3);
                        var_a1 = 0x20;
                        if (D_800E3D68 == 0xFF) {
                            var_a1 = 0xFF;
                        }
                        func_800C87C4(var_s0, var_a1, temp_a2);
                    }
                }
            }
        }
        var_s0 = M2C_FIELD(var_s0, s32 *, 0x5C) + 0x20;
    } while (var_s0 != *D_800E3D7C);
}

