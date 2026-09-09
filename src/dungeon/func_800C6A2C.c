#include "common.h"

typedef struct S_800CC18C_0 {
    s32 unk_00;
    s32 unk_04;
    u8 pad_08[0x13];
    u8 unk_1B;
    u8 pad_1C[0xF];
    u8 unk_2B;
} S_800CC18C_0;   /* arg0 in func_800CC18C; pointer addresses record offset 0x18 */


extern u8 D_800E3D40[];
extern u8 D_800E1BDA[];
extern s32 func_80099844(void *, void *);
extern s32 func_800A56E0(u32);
extern s32 func_800A6508(void);
extern s32 func_800A6D30(void *, s32, s32, s32);
extern s32 func_800AA5E4(void *, s32, s32, void *);

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

s32 func_800CC18C(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    register s32 value ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    register s32 numerator ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 range;
    register s32 remainder ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s16 var_s1;
    s16 temp_s16;
    s32 temp_v1;
    s32 var_v1;

    var_s1 = 0;
    if (D_800E3D40[0] == 0) {
        numerator = func_800A6D30(arg0, arg1, arg2, arg3) & 0xFFFF;
        range = ((S_800CC18C_0 *)((u8 *)arg0 - 0x18))->unk_1B;
        if (range != 0) {
            value = range;
            ASM_KEEP(value);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            remainder = numerator % value;
            value = remainder;
            goto value_ready;
        }
    }
    value = 0;
value_ready:
    if (value < 0x40) {
        func_800AA5E4(arg0, ((S_800CC18C_0 *)((u8 *)arg0 - 0x18))->unk_00, ((S_800CC18C_0 *)((u8 *)arg0 - 0x18))->unk_04, arg0);
        func_800A56E0(0x705);
        if (D_800E3D40[0] != 0) {
            var_s1 = -1;
        }
        temp_v1 = ((S_800CC18C_0 *)((u8 *)arg0 - 0x18))->unk_2B == 0;
    } else {
        var_s1 = 1;
        temp_v1 = (((S_800CC18C_0 *)((u8 *)arg0 - 0x18))->unk_2B == 0) * 2;
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
