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
#define M2C_UNALIGNED32(expr) (expr)

extern u8 D_80024004[24];

void func_8002506C(void *arg0, s32 arg1) {
    u16 sp[12];
    s32 var_v0;
    void *temp_a0;
    void *temp_v1;

    __builtin_memcpy(sp, D_80024004, 24);
    if ((u32)(arg1 & 0xFFFF) >= 6U) {
        arg1 = 0;
    }
    var_v0 = arg1 << 0x10;
    temp_v1 = (u8 *)sp + (var_v0 >> 0xE);
    temp_a0 = M2C_FIELD(arg0, void **, -0x14);
    M2C_FIELD(temp_a0, u16 *, 0x1C) = (u16)M2C_FIELD(temp_v1, u16 *, 0);
    M2C_FIELD(temp_a0, u16 *, 0x1E) = (u16)M2C_FIELD(temp_v1, u16 *, 2);
}
