/* cfail-repair: unary-star-typing; preserve the warm source shape */
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

struct S_8003E2D8 {
    u8 byte_0;
};
extern struct S_8003E2D8 D_80083160;

s32 func_8008C134(s32 arg0, s32 arg1) {
    register u8 *temp_a3 ASM_REG("$7");
    register u8 *temp_a2 ASM_REG("$6");

    temp_a3 = (u8 *)&D_80083160;
    ASM_KEEP(temp_a3);
    temp_a2 = temp_a3 + 0x1DC;
    ASM_KEEP(temp_a2);
    return *(u16 *)(((s32) (((M2C_FIELD(temp_a2, u16 *, 0x18) & arg0) + ((s16) (M2C_FIELD(temp_a2, u16 *, 0x1A) & arg1) << M2C_FIELD(temp_a2, s16 *, 0x14))) << 0x10) >> 0xF) + M2C_FIELD(temp_a3, s32 *, 0x1DC)) & 0x3FFF;
}
