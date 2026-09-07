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
#define M2C_BITWISE(type, expr) ((type)(expr))
#define M2C_LWL(expr) (expr)
#define M2C_FIRST3BYTES(expr) (expr)
#define M2C_UNALIGNED32(expr) (expr)
#define M2C_ERROR(desc) (0)
#define M2C_TRAP_IF(cond) (0)
#define M2C_BREAK() (0)
#define M2C_SYNC() (0)
#define GLUE_F64(a, b) (0.0)
#define MULT_HI(a, b) (0)
#define MULTU_HI(a, b) (0)
#define DMULT_HI(a, b) (0)
#define DMULTU_HI(a, b) (0)
#define CLZ(x) (0)
#define REVERSE_BITS(x) (0)
#define ROTATE_RIGHT(x, shift) (0)
#define ARM_RRX(x, carry) (0)
#define BSWAP32(x) (0)
#define BSWAP16(x) (0)
#define BSWAP16X2(x) (0)
#define M2C_CARRY 0
#define M2C_OVERFLOW(a) (0)
#define M2C_MEMCPY_ALIGNED memcpy
#define M2C_MEMCPY_UNALIGNED memcpy
#define M2C_STRUCT_COPY memcpy

s32 func_80065F90();

s32 func_800BCE7C(void *arg0) {
    s32 temp_a0;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 temp_v1_3;

    if (M2C_FIELD(arg0, s32 *, 0x154) != 0) {
        if (M2C_FIELD(arg0, s32 *, 0x160) == 0) {
            goto block_6;
        }
        M2C_FIELD(arg0, s32 *, 0x164) = func_80065F90(M2C_FIELD(arg0, s16 *, 0x156), (s16) M2C_FIELD(arg0, s32 *, 0x154));
        temp_v0 = func_80065F90(M2C_FIELD(arg0, s16 *, 0x162), (s16) M2C_FIELD(arg0, s32 *, 0x160));
        M2C_FIELD(arg0, s32 *, 0x170) = temp_v0;
        temp_v0_2 = temp_v0 - M2C_FIELD(arg0, s32 *, 0x164);
        temp_v1_2 = (0x1000 - temp_v0_2) & 0xFFF;
        M2C_FIELD(arg0, s32 *, 0x180) = temp_v1_2;
        M2C_FIELD(arg0, s32 *, 0x170) = temp_v0_2;
        if (temp_v1_2 >= 0x801) {
            return 0;
        }
        if (M2C_FIELD(arg0, s32 *, 0x15C) == 0) {
            goto block_6;
        }
        temp_v0_3 = func_80065F90(M2C_FIELD(arg0, s16 *, 0x15E), (s16) M2C_FIELD(arg0, s32 *, 0x15C));
        M2C_FIELD(arg0, s32 *, 0x16C) = temp_v0_3;
        temp_v0_4 = temp_v0_3 - M2C_FIELD(arg0, s32 *, 0x164);
        temp_v1_3 = (M2C_FIELD(arg0, s32 *, 0x170) - temp_v0_4) & 0xFFF;
        M2C_FIELD(arg0, s32 *, 0x17C) = temp_v1_3;
        M2C_FIELD(arg0, s32 *, 0x16C) = temp_v0_4;
        if (temp_v1_3 >= 0x801) {
            return 0;
        }
        if (M2C_FIELD(arg0, s32 *, 0x158) != 0) {
            goto block_7;
        }
block_6:
        ASM_KEEP(arg0);
        return 1;
block_7:
        temp_v0_5 = func_80065F90(M2C_FIELD(arg0, s16 *, 0x15A), (s16) M2C_FIELD(arg0, s32 *, 0x158));
        M2C_FIELD(arg0, s32 *, 0x168) = temp_v0_5;
        temp_a0 = (temp_v0_5 - M2C_FIELD(arg0, s32 *, 0x164)) & 0xFFF;
        M2C_FIELD(arg0, s32 *, 0x168) = temp_a0;
        if (temp_a0 < 0x801) {
            temp_v1 = (M2C_FIELD(arg0, s32 *, 0x16C) - temp_a0) & 0xFFF;
            M2C_FIELD(arg0, s32 *, 0x178) = temp_v1;
            return temp_v1 < 0x801;
        }
        return 0;
    }
    return 1;
}
