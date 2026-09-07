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

typedef struct {
    u8 pad_00[0x1E];
    u16 field_1E;
    u8 pad_20[8];
    u8 field_28;
    u8 field_29;
} TargetState;

extern s16 D_80025E80[5];
extern u8 D_80020000[];
extern s32 D_800814A0;
extern void *D_80024008[];
extern void func_800246C0() __attribute__((noreturn));

M2C_UNK func_818FEDEC(void *arg0, s32 arg1, void *arg2) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6, &&jt_c7 };
    u16 temp_v0;
    s32 temp_v1;
    s32 *page_base;

    temp_v0 = M2C_FIELD(arg0, u16 *, 2);
    *D_80025E80 = 1;
    M2C_FIELD(arg0, u16 *, 2) = (u16) (temp_v0 - 1);
    M2C_FIELD(arg2, s16 *, 0x1C) = 0x2000;
    M2C_FIELD(arg2, s16 *, 0x1E) = 0x2000;
    if (M2C_FIELD(arg0, s16 *, 0x1C) != 0) {
        goto block_9;
    }
    temp_v1 = M2C_FIELD(arg0, s16 *, 0x1E);
    M2C_FIELD(arg0, s16 *, 0x1C) = 0;
    if ((u32) temp_v1 >= 8U) {
        goto block_10;
    }
    (void)jt_keep; goto *D_80024008[(u32)(temp_v1)];
jt_c0:
jt_c1:
jt_c2:
jt_c4:
jt_c5:
jt_c6:
    M2C_FIELD(arg0, s16 *, 0x1E) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x1E) + 1);
    M2C_FIELD(arg0, u8 *, 0x28) = (u8) (M2C_FIELD(arg0, u8 *, 0x28) + 0x20);
    func_800246C0();
    return;
jt_c3:
    M2C_FIELD(arg0, u16 *, 0x1E) += 1;
    M2C_FIELD(arg0, u8 *, 0x28) -= 0x60;
    M2C_FIELD(arg0, u8 *, 0x29) += 0x20;
    func_800246C0();
    return;
jt_c7:
    {
        u16 c7_byte;
        s32 c7_other;
        c7_byte = M2C_FIELD(arg0, u8 *, 0x28);
        c7_other = M2C_FIELD(arg0, u8 *, 0x29);
        M2C_FIELD(arg0, s16 *, 0x1E) = 0;
        c7_byte = c7_byte - 0x60;
        c7_other = c7_other - 0x20;
        M2C_FIELD(arg0, u8 *, 0x28) = c7_byte;
        M2C_FIELD(arg0, u8 *, 0x29) = c7_other;
        func_800246C0();
        return;
    }
block_9:
    M2C_FIELD(arg0, s16 *, 0x1C) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x1C) + 1);
block_10:
    if ((s16) M2C_FIELD(arg0, u16 *, 2) > 0) {
        goto block_12;
    }
    M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
    D_800814A0 = D_800814A0 | 0x8000;
block_12:
    return;
}
