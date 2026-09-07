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
#define M2C_BREAK() ((void)0)
#define M2C_SYNC() ((void)0)
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

extern s32 func_800A6D30();

void func_800ADD20(void *arg0, s32 arg1) {
    s32 temp_v1;
    u16 temp_v0;

    temp_v1 = M2C_FIELD(arg0, s32 *, 0x14);
    if (!(temp_v1 & 0x8000)) {
        M2C_FIELD(arg0, s32 *, 0x14) = (s32) (temp_v1 | 0x8000);
        if (((s32) (func_800A6D30() & 0xFFFF) % arg1) != 0) {
            temp_v0 = M2C_FIELD(arg0, u16 *, 0x98);
            temp_v0 = (u16) (temp_v0 & 0xFEFF);
        } else {
            temp_v0 = M2C_FIELD(arg0, u16 *, 0x98);
            temp_v0 = (u16) (temp_v0 | 0x100);
        }
        M2C_FIELD(arg0, u16 *, 0x98) = temp_v0;
    }
}
