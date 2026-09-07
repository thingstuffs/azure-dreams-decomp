#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;
typedef s8 M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK D_800E2970[];
extern M2C_UNK D_800E2C40[];

void func_800177D8(s16 arg0, s8 arg1, s8 arg2, s16 arg3) {
    register s32 temp_a1 ASM_REG("$5");
    u16 temp_v0;
    void *base_2970;
    void *base_2c40;
    void *temp_t0;
    void *temp_v0_2;

    base_2970 = (void *)D_800E2970;
    temp_t0 = (arg0 * 0x14) + base_2970;
    if (M2C_FIELD(temp_t0, s16 *, 0xA) != 0) {
        temp_a1 = arg0 << 6;
        ASM_KEEP(temp_a1);
        base_2c40 = (void *)D_800E2C40;
        do { temp_v0 = M2C_FIELD(temp_t0, u16 *, 0xE); } while (0);
        M2C_FIELD(temp_t0, void **, 0x10) = temp_a1 + base_2c40;
        temp_v0_2 = ((s32)(temp_v0 << 0x10) >> 0xE) + temp_a1 + base_2c40;
        M2C_FIELD(temp_t0, u16 *, 0xE) = (u16)(temp_v0 + 1);
        M2C_FIELD(temp_v0_2, s16 *, 2) = arg3;
        M2C_FIELD(temp_v0_2, s8 *, 0) = arg1;
        M2C_FIELD(temp_v0_2, s8 *, 1) = arg2;
    }
}

/* MECHANISM: Frameless leaf under the true-space name, with named bases hoisting both global address pairs.
   The row offset is guarded in $a1 immediately after definition, before the lhu temporary is born.
   This preserves retail's $a0/$a1 and $v0/$v1 roles while keeping the 29-word schedule exact. */
