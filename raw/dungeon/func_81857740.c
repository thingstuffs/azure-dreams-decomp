#include "common.h"

typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;

typedef s32 M2C_UNK;
typedef s8 M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

s16 func_8006649C();
s32 func_80069EF8();
extern s32 D_800814A0;

void func_80024F40(void *arg0) {
    s16 temp_v1;
    void *temp_v0;

    temp_v0 = M2C_FIELD(arg0, void **, 0);
    M2C_FIELD(temp_v0, u16 *, 0x52) =
        (u16)(M2C_FIELD(temp_v0, u16 *, 0x52) | 0x8000);
    M2C_FIELD(arg0, s16 *, 0x42) =
        func_8006649C((func_80069EF8() & 0xF) * 0x10, 0x1F8);
    temp_v1 = M2C_FIELD(arg0, s16 *, 0x4A);
    if (temp_v1 == 0)
        goto status_zero;
    if (temp_v1 == 1)
        goto status_one;
    goto common_return;

status_zero:
    if ((u8)M2C_FIELD(arg0, u8 *, 0x34) >= 0x31U)
        goto status_zero_high;
    M2C_FIELD(arg0, s32 *, 0x34) = 0;
    M2C_FIELD(arg0, u16 *, 0x4A)++;
    goto common_return;

status_zero_high:
    M2C_FIELD(arg0, s32 *, 0x34) =
        M2C_FIELD(arg0, s32 *, 0x34) - 0x303030;
    goto common_return;

status_one:
        M2C_FIELD(arg0, u16 *, -2) =
            (u16)(M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        D_800814A0 |= 0x8000;
        goto common_return;

common_return:
    return;
}
