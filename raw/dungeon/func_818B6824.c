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

extern s32 func_8009D218(void *, s32);
extern s32 func_800A6870(s32);
extern void func_800AD4D0(void *);
extern s16 func_800AD568(void *, s32);
extern M2C_UNK func_800B4C7C(s32, void *, s32, s32);

void func_818B6824(void *arg0, s32 arg1) {
    register s32 temp_v1 ASM_REG("$3");
    register s32 var_a1;

    if (func_8009D218(arg0, 1) == 0) {
        temp_v1 = func_800A6870(arg1 & 0xFF) + 8;
        var_a1 = temp_v1;
        if (M2C_FIELD(arg0, u8 *, 0x28) & 1) {
            var_a1 = temp_v1 << 1;
        }
        M2C_FIELD(arg0, u16 *, 0x64) = (u16) (M2C_FIELD(arg0, u16 *, 0x64) + var_a1);
        func_800AD568(arg0, var_a1);
        func_800B4C7C(0x8004, arg0, (s16) M2C_FIELD(arg0, u16 *, 0x64), 1);
        func_800AD4D0(arg0);
    }
}
