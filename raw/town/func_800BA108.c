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

extern u16 D_80162004[];

void func_800B7868(s16 arg0, s16 arg1, u16 *arg2) {
    s16 temp_v0;
    s16 temp_v0_2;
    s16 var_t2;
    s16 var_a1;
    u16 temp_t3;
    u16 temp_t4;
    u16 temp_v1;

    temp_t4 = *arg2++;
    temp_t3 = *arg2++;
    var_t2 = 0;
    while ((var_t2 << 0x10) < (temp_t3 << 0x10)) {
        var_a1 = 0;
        while (var_a1 < (s16) temp_t4) {
            temp_v1 = *arg2;
            if (temp_v1 != 0) {
                D_80162004[((var_t2 + arg1) << 7) + var_a1 + arg0] = temp_v1;
            }
            temp_v0_2 = var_a1 + 1;
            var_a1 = temp_v0_2;
            arg2++;
        }
        temp_v0 = var_t2 + 1;
        var_t2 = temp_v0;
    }
}
