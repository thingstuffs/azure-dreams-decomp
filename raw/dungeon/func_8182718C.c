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

extern int D_800814A0[];
extern u8 D_80045340[];
extern void func_80024A7C(void) __attribute__((noreturn));

void func_8182718C(void *arg0, void *arg1, void *arg2) {
    s16 temp_v1_2;
    u16 temp_v0;
    u16 temp_v0_2;
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, void **, 0);
    M2C_FIELD(temp_v1, u16 *, 0x52) = (s16) (M2C_FIELD(temp_v1, u16 *, 0x52) | 0x8000);
    temp_v1_2 = M2C_FIELD(arg0, s16 *, 0x4C);
    if (temp_v1_2 == 0) {
        goto zero_state;
    }
    if (temp_v1_2 == 1) {
        goto one_state;
    }
    func_80024A7C();

zero_state:
    {
        u16 temp_zero_4c;
        u16 temp_zero_4e;

        temp_v0_2 = M2C_FIELD(arg0, u16 *, 0x48) - 1;
        M2C_FIELD(arg0, u16 *, 0x48) = temp_v0_2;
        if ((temp_v0_2 << 0x10) <= 0) {
            func_8004491C(arg0 - 0x20, D_80045340);
            temp_zero_4c = M2C_FIELD(arg0, u16 *, 0x4C);
            temp_zero_4e = M2C_FIELD(arg0, u16 *, 0x4E);
            M2C_FIELD(arg0, u16 *, 0x48) = temp_zero_4e;
            M2C_FIELD(arg0, u16 *, 0x4C) = (u16) (temp_zero_4c + 1);
            func_80024A7C();
        }
        goto done;
    }

one_state:
    {
        temp_v0 = M2C_FIELD(arg0, u16 *, 0x48);
        M2C_FIELD(arg0, u16 *, 0x48) = (u16) (temp_v0 - 1);
        if ((temp_v0 << 0x10) <= 0) {
            func_800478B8(arg2);
            M2C_FIELD(arg0, u16 *, 0x48) = (u16) M2C_FIELD(arg0, u16 *, 0x4E);
        }
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0x6000) {
            M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
            D_800814A0[0] = (s32) (D_800814A0[0] | 0x8000);
        }
    }

done:
    ;
}
