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

extern s8 D_80016000[];

void func_80019DE0(void *arg0) {
    u16 temp_v0;
    u16 temp_v0_2;
    u32 temp_shift;
    void *temp_a0;
    void *temp_a0_2;

    M2C_FIELD(M2C_FIELD(M2C_FIELD(&D_80016000, void **, 0), void **, 0x20), M2C_UNK (**)(M2C_UNK), 0x258)(1);
    temp_v0 = M2C_FIELD(arg0, u16 *, 0);
    temp_a0 = M2C_FIELD(M2C_FIELD(D_80016000, void **, 0), void **, 0x1C);
    temp_shift = (u32) temp_v0 << 0x10;
    M2C_FIELD(temp_a0, s32 *, 4) = (s32) (M2C_FIELD(temp_a0, s32 *, 4) + ((s32) (((s32) temp_shift >> 0x10) + (temp_shift >> 0x1F)) >> 1));
    temp_v0_2 = M2C_FIELD(arg0, u16 *, 2);
    temp_a0_2 = M2C_FIELD(M2C_FIELD(D_80016000, void **, 0), void **, 0x1C);
    temp_shift = (u32) temp_v0_2 << 0x10;
    M2C_FIELD(temp_a0_2, s32 *, 8) = (s32) (M2C_FIELD(temp_a0_2, s32 *, 8) + ((s32) (((s32) temp_shift >> 0x10) + (temp_shift >> 0x1F)) >> 1));
}

/* MECHANISM: The true-space function holds the hi/lo-class D_80016000 page in s0
   and arg0 in s1 across the indirect call; all three root loads use one pointer slot.
   The narrow u16 loads plus explicit s16 rounding preserve the two arithmetic sequences. */
