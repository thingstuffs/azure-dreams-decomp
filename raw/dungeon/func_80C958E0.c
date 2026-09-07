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

extern s32 D_80083460[3];
extern u8 D_8017102C[];
extern M2C_UNK D_801752E4;
extern void func_800A2B04(void *, u8, u8);
extern void func_800AAA54(void *, void *, void *, void *);
extern void func_800AD4D0(void *);
extern void func_800B66C8(void *);
extern void func_800419EC(s32, s32);

void func_801730E0(void *arg0, void *arg1, void *arg2, void *arg3) {
    s16 temp_v1;
    u16 temp_v0;
    s16 var_v1;
    s32 *var_a0;
    u8 *var_v0;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    if (temp_v1 == 1)
        goto case_1;
    if (temp_v1 < 2) {
        if (temp_v1 == 0)
            goto case_0;
        goto epilogue;
    }
    if (temp_v1 == 2)
        goto case_2;
    goto epilogue;

case_0:
        func_800AD4D0(arg3);
        M2C_FIELD(arg1, s32 *, 0x10) = 0;
        M2C_FIELD(arg1, s32 *, 0xC) = 0;
        func_800B66C8(arg1);
        func_800B66C8(arg1);
        func_800B66C8(arg1);
        func_800B66C8(arg1);
        func_800419EC(4, 6);
        M2C_FIELD(arg0, u8 *, 0x9B) = M2C_FIELD(arg0, u8 *, 0x9B) + 1;
        if (M2C_FIELD(arg3, u8 *, 0x28) != 0) {
            if (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000) {
                M2C_FIELD(arg0, u16 *, 0x96) = 0;
                M2C_FIELD(arg0, u8 *, 0x9B) = 2;
                goto epilogue;
            }
            var_v1 = -1U;
            if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x228)
                var_v1 = 8;
            M2C_FIELD(arg0, u16 *, 0x96) = var_v1;
            goto block_15;
        }
        M2C_FIELD(arg1, s32 *, 0x14) = 0;
        M2C_FIELD(arg1, s32 *, 0x10) = 0;
        M2C_FIELD(arg1, s32 *, 0xC) = 0;
        func_800AAA54(arg0, arg1, arg2, &D_801752E4);
        goto epilogue;

case_1:
block_15:
        if (M2C_FIELD(arg0, s16 *, 0x96) > 0) {
            temp_v0 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
            M2C_FIELD(arg0, u16 *, 0x96) = temp_v0;
            goto block_20;
        }
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0x6000)
            M2C_FIELD(arg0, u16 *, 0x96) = 0;
block_20:
        if (M2C_FIELD(arg0, s16 *, 0x96) != 0)
            goto epilogue;
        if (M2C_FIELD(arg3, u8 *, 0x28) == 0) {
            M2C_FIELD(arg1, s32 *, 0x14) = 0;
            M2C_FIELD(arg1, s32 *, 0x10) = 0;
            M2C_FIELD(arg1, s32 *, 0xC) = 0;
            func_800AAA54(arg0, arg1, arg2, &D_801752E4);
            goto epilogue;
        }
        func_800419EC(1, 1);
        M2C_FIELD(arg0, u16 *, 0x96) = 8;
        M2C_FIELD(arg0, u8 *, 0x9B) = M2C_FIELD(arg0, u8 *, 0x9B) + 1;
        goto epilogue;

case_2:
        temp_v0 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
        M2C_FIELD(arg0, u16 *, 0x96) = temp_v0;
        if ((temp_v0 << 0x10) > 0)
            goto epilogue;
        M2C_FIELD(arg1, s32 *, 0x14) = 0;
        M2C_FIELD(arg1, s32 *, 0x10) = 0;
        M2C_FIELD(arg1, s32 *, 0xC) = 0;
        func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
        var_a0 = D_80083460;
        if (var_a0[4] == (arg3 - 0x20)) {
            var_a0[4] = var_a0[4] & 0x7FFFFFFF;
        }
        var_v0 = D_8017102C;
        M2C_FIELD(arg0, u8 **, 0x8C) = var_v0;
        goto epilogue;

epilogue:
    return;
}
