#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif
/*
 * This header contains macros emitted by m2c in "valid syntax" mode,
 * which can be enabled by passing `--valid-syntax` on the command line.
 *
 * In this mode, unhandled types and expressions are emitted as macros so
 * that the output is compilable without human intervention.
 */


/* Unknown types */
typedef s32 M2C_UNK;
typedef s8  M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

/* Unknown field access, like `*(type_ptr) &expr->unk_offset` */
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

/* Bitwise (reinterpret) cast */
#define M2C_BITWISE(type, expr) ((type)(expr))

/* Unaligned reads */
#define M2C_LWL(expr) (expr)
#define M2C_FIRST3BYTES(expr) (expr)
#define M2C_UNALIGNED32(expr) (expr)

/* Unhandled instructions */
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

/* Carry/overflow bits from partially-implemented instructions */
#define M2C_CARRY 0
#define M2C_OVERFLOW(a) (0)

/* Memcpy patterns */
#define M2C_MEMCPY_ALIGNED memcpy
#define M2C_MEMCPY_UNALIGNED memcpy
#define M2C_STRUCT_COPY memcpy

extern u8 D_80083160[];

void func_8009D808(void *arg0, void *arg1, void *arg2) {
    s16 temp_a3;
    s16 temp_a3_2;
    s16 temp_a3_3;
    s16 temp_a3_4;
    s32 temp_v1;
    s32 temp_v1_2;
    u16 temp_v0;
    u16 temp_v0_2;
    s32 temp_t1;
    u8 *base;
    u8 *temp_t2;
    void *var_t0;

    temp_v0 = M2C_FIELD(arg0, u16 *, 0);
    M2C_FIELD(arg2, u16 *, 0) = temp_v0;
    M2C_FIELD(arg1, u16 *, 0) = temp_v0;
    temp_v0_2 = M2C_FIELD(arg0, u16 *, 2);
    M2C_FIELD(arg2, u16 *, 2) = temp_v0_2;
    M2C_FIELD(arg1, u16 *, 2) = temp_v0_2;
    base = D_80083160;
    temp_t2 = base + 0x1DC;
    if ((s16) M2C_FIELD(arg1, u16 *, 0) < 0) {
        M2C_FIELD(arg2, u16 *, 0) = 0U;
        M2C_FIELD(arg1, u16 *, 0) = 0U;
    }
    if ((s16) M2C_FIELD(arg1, u16 *, 2) < 0) {
        M2C_FIELD(arg2, u16 *, 2) = 0U;
        M2C_FIELD(arg1, u16 *, 2) = 0U;
    }
    temp_t1 = 0x40;
    var_t0 = arg0;
    do {
        temp_a3 = M2C_FIELD(var_t0, s16 *, 0);
        if ((s16) M2C_FIELD(arg1, u16 *, 0) < temp_a3) {
            M2C_FIELD(arg1, u16 *, 0) = (u16) M2C_FIELD(var_t0, s16 *, 0);
            temp_v1 = (temp_t1 << ((s16 *)temp_t2)[0xA]) - 1;
            if (temp_v1 < temp_a3) {
                M2C_FIELD(arg1, u16 *, 0) = (u16) temp_v1;
            }
        }
        temp_a3_2 = M2C_FIELD(var_t0, s16 *, 0);
        if ((s16) M2C_FIELD(arg2, u16 *, 0) > temp_a3_2) {
            M2C_FIELD(arg2, u16 *, 0) = (u16) M2C_FIELD(var_t0, s16 *, 0);
            if (temp_a3_2 < 0) {
                M2C_FIELD(arg2, u16 *, 0) = 0U;
            }
        }
        temp_a3_3 = M2C_FIELD(var_t0, s16 *, 2);
        if ((s16) M2C_FIELD(arg1, u16 *, 2) < temp_a3_3) {
            M2C_FIELD(arg1, u16 *, 2) = (u16) M2C_FIELD(var_t0, s16 *, 2);
            temp_v1_2 = (temp_t1 << ((s16 *)temp_t2)[0xB]) - 1;
            if (temp_v1_2 < temp_a3_3) {
                M2C_FIELD(arg1, u16 *, 2) = (u16) temp_v1_2;
            }
        }
        temp_a3_4 = M2C_FIELD(var_t0, s16 *, 2);
        if ((s16) M2C_FIELD(arg2, u16 *, 2) > temp_a3_4) {
            M2C_FIELD(arg2, u16 *, 2) = (u16) M2C_FIELD(var_t0, s16 *, 2);
            if (temp_a3_4 < 0) {
                M2C_FIELD(arg2, u16 *, 2) = 0U;
            }
        }
        var_t0 += 8;
    } while ((s32) var_t0 < (s32) (arg0 + 0x20));
}
