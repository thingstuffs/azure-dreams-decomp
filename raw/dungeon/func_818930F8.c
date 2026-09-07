#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_80024824();
extern M2C_UNK func_800478B8();
extern s32 D_800814A0[3];

void func_818930F8(void *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    s16 temp_a3;
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, void **, 0);
    M2C_FIELD(temp_v1, u16 *, 0x14) = (u16) (M2C_FIELD(temp_v1, u16 *, 0x14) + 1);
    M2C_FIELD(arg0, u16 *, 4) = (u16) (M2C_FIELD(arg0, u16 *, 4) + 1);
    func_800478B8(arg2);
    temp_a3 = (s16) M2C_FIELD(arg0, u16 *, 4);
    if (temp_a3 < 5) {
        func_80024824(M2C_FIELD(arg0, void **, 0), arg1, 8, (s16) ((temp_a3 * 0x10) - 0x40));
    }
    if ((s16) M2C_FIELD(arg0, u16 *, 4) > M2C_FIELD(arg0, s16 *, 6)) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        D_800814A0[0] = (s32) (D_800814A0[0] | 0x8000);
    }
}
