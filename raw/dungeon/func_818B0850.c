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

extern s32 func_8009D218(void *arg0, s32 arg1);
extern s32 func_800A6870(s32 arg0);
extern void func_800AD4D0(void *arg0);
extern void func_800AD568(void *arg0, s32 arg1);
extern void func_800B4C7C(s32 arg0, void *arg1, s32 arg2, s32 arg3);

void func_818B0850(void *arg0, s32 arg1) {
    if (func_8009D218(arg0, 4) == 0) {
        register s32 temp_v1 ASM_REG("$3");
        s16 temp_v0;
        s32 var_a1;

        temp_v1 = func_800A6870(arg1 & 0xFF) + 8;
        temp_v0 = M2C_FIELD(arg0, u8 *, 0x28) & 4;
        var_a1 = temp_v1;
        if (temp_v0) {
            temp_v0 = (s32) (temp_v1 << 16) >> 18;
            var_a1 = temp_v1 + temp_v0;
        }
        M2C_FIELD(arg0, u16 *, 0x64) = (u16) (M2C_FIELD(arg0, u16 *, 0x64) + var_a1);
        func_800AD568(arg0, var_a1);
        func_800B4C7C(0x8004, arg0, (s16) M2C_FIELD(arg0, u16 *, 0x64), 1);
        func_800AD4D0(arg0);
    }
}
