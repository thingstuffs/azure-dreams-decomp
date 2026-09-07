#include "common.h"

extern u8 D_800E3D40[];
extern u8 D_800E1BDA[];
extern s32 func_80099844(void *, void *);
extern s32 func_800A56E0(u32);
extern s32 func_800A6508(void);
extern s32 func_800A6D30(void);
extern s32 func_800AA5E4(void *, s32, s32, void *);

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

s32 func_800CC18C(void *arg0) {
    register s32 value ASM_REG("$2");
    register s32 numerator ASM_REG("$4");
    s32 range;
    register s32 remainder ASM_REG("$3");
    s16 var_s1;
    s16 temp_s16;
    s32 temp_v1;
    s32 var_v1;

    var_s1 = 0;
    if (D_800E3D40[0] == 0) {
        numerator = func_800A6D30() & 0xFFFF;
        range = M2C_FIELD(arg0, u8 *, 3);
        if (range != 0) {
            value = range;
            ASM_KEEP(value);
            remainder = numerator % value;
            value = remainder;
            goto value_ready;
        }
    }
    value = 0;
value_ready:
    if (value < 0x40) {
        func_800AA5E4(arg0, M2C_FIELD(arg0, s32 *, -0x18), M2C_FIELD(arg0, s32 *, -0x14), arg0);
        func_800A56E0(0x705);
        if (D_800E3D40[0] != 0) {
            var_s1 = -1;
        }
        temp_v1 = M2C_FIELD(arg0, u8 *, 0x13) == 0;
    } else {
        var_s1 = 1;
        temp_v1 = (M2C_FIELD(arg0, u8 *, 0x13) == 0) * 2;
    }
    var_v1 = temp_v1;
    if (var_v1 != 0) {
        if (var_v1 == 1) {
            func_80099844(arg0, &D_800E1BDA);
        } else {
            func_800A6508();
        }
    }
    temp_s16 = var_s1;
    if (temp_s16 >= 0) {
        goto nonnegative;
    }
    goto negative;
negative:
    return 0;
nonnegative:
    if (temp_s16 != 0) {
        var_v1 = 1;
    } else {
        var_v1 = -1;
    }
    return var_v1;
}
