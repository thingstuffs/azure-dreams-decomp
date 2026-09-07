#include "common.h"

extern void func_80042BDC();
extern s32 func_800A4B38();
extern void func_800A5DFC();

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

s32 func_800A4ACC(void *arg0) {
    s32 var_s1;
    s8 temp_v1;
    s8 temp_v1_2;
    u8 temp_a1;
    void *var_s0;

    var_s1 = 3;
    var_s0 = arg0 + 6;
loop_1:
    temp_v1 = M2C_FIELD(var_s0, s8 *, 0x2C);
    if (temp_v1 != 0) {
        if (temp_v1 == 5) {
            func_800A5DFC(arg0, M2C_FIELD(arg0, s32 *, -0x18));
        }
        temp_v1_2 = M2C_FIELD(var_s0, s8 *, 0x2D);
        if (temp_v1_2 != 0) {
            if (temp_v1_2 > 0) {
                return func_800A4B38() - 1;
            }
            if (temp_v1_2 < 0) {
                M2C_FIELD(var_s0, s8 *, 0x2D) =
                    (s8)((u8)M2C_FIELD(var_s0, s8 *, 0x2D) + 1);
            }
            if (M2C_FIELD(var_s0, s8 *, 0x2D) == 0) {
                temp_a1 = (u8)M2C_FIELD(var_s0, s8 *, 0x2C);
                M2C_FIELD(var_s0, s8 *, 0x2C) = 0;
                func_80042BDC(arg0, (s8)temp_a1);
            }
        }
    }
    var_s1 -= 1;
    var_s0 -= 2;
    if (var_s1 >= 0) {
        goto loop_1;
    }
}
