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

M2C_UNK func_80099844();
s32 func_800A48F0();
s32 func_800A6D30();
M2C_UNK func_800DC1B8();
extern s32 D_800DCF20;
extern M2C_UNK D_800E1937;
extern M2C_UNK D_800E1A6D;

s32 func_800C8DB0(void *arg0, s16 arg1, s8 arg2) {
    s16 temp_v1;
    s32 temp_a0;
    u8 temp_a0_2;

    if ((M2C_FIELD(arg0, u8 *, 0x13) != 0) && ((M2C_FIELD(arg0, s32 *, 8) & 0xFF0000FF) || (M2C_FIELD(arg0, u8 *, 0xE) != 0))) {
        temp_a0_2 = M2C_FIELD(arg0, u8 *, 0xE);
        if (((u8) M2C_FIELD(arg0, s32 *, 8) + M2C_FIELD(arg0, u8 *, 0xB) + temp_a0_2) != 0) {
            temp_a0 = func_800A6D30(temp_a0_2) & 0xFFFF;
            if (M2C_FIELD(arg0, u8 *, 3) != 0) {
                temp_v1 = temp_a0 % M2C_FIELD(arg0, u8 *, 3);
            } else {
                temp_v1 = 0;
            }
            if ((temp_v1 < arg1 || arg1 == 0xFF) && (s16)func_800A48F0(arg0, 6, arg2) >= 0) {
                func_80099844(arg0, &D_800E1937);
                if (M2C_FIELD(arg0, u8 *, 0x13) == 0) {
                    func_800DC1B8(D_800DCF20);
                }
                return 1;
            }
        }
    }
    if (M2C_FIELD(arg0, s32 *, 0x14) & 0x4000) {
        func_80099844(arg0, &D_800E1A6D);
    }
    return 0;
}
