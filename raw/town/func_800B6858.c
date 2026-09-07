/* cfail-repair: tf7-phase1-cache-v3 */
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

s32 func_8004DC14();                    /* extern */

void func_800B3FB8(void *arg0, void *arg1, s32 arg2) {
    s32 temp_s1;
    void *temp_s3;

    temp_s1 = arg2 * 4;
    temp_s3 = M2C_FIELD(temp_s1 + M2C_FIELD(arg0, s32 *, 0x5C), void **, 0);
    M2C_FIELD(temp_s3, s32 *, 0) = (s32) M2C_FIELD(arg0, s32 *, 0x20);
    M2C_FIELD(M2C_FIELD(temp_s3, void **, 4), u16 *, 8) = (u16) M2C_FIELD(arg1, u16 *, 4);
    M2C_FIELD(M2C_FIELD(temp_s3, void **, 4), u16 *, 0xA) = (u16) M2C_FIELD(arg1, u16 *, 6);
    temp_s3 = M2C_FIELD((temp_s1 + M2C_FIELD(arg0, s32 *, 0x5C)), void **, 0x30);
    M2C_FIELD(temp_s3, s32 *, 0) = (s32) M2C_FIELD(arg1, s32 *, 0x10);
    M2C_FIELD(M2C_FIELD(temp_s3, void **, 4), u16 *, 8) = (u16) M2C_FIELD(arg1, u16 *, 8);
    M2C_FIELD(M2C_FIELD(temp_s3, void **, 4), u16 *, 0xA) = (u16) M2C_FIELD(arg1, u16 *, 0xA);
    temp_s3 = M2C_FIELD((temp_s1 + M2C_FIELD(arg0, s32 *, 0x5C)), void **, 0x18);
    M2C_FIELD(temp_s3, s32 *, 0) = func_8004DC14(M2C_FIELD(arg1, s32 *, 0), 1);
    M2C_FIELD(M2C_FIELD(temp_s3, void **, 4), u16 *, 8) = (u16) M2C_FIELD(arg1, u16 *, 0xC);
    M2C_FIELD(M2C_FIELD(temp_s3, void **, 4), u16 *, 0xA) = (u16) M2C_FIELD(arg1, u16 *, 0xE);
    temp_s3 = M2C_FIELD((temp_s1 + M2C_FIELD(arg0, s32 *, 0x5C)), void **, 0x48);
    M2C_FIELD(temp_s3, s32 *, 0) = func_8004DC14(M2C_FIELD(arg1, s32 *, 0), 0x90);
    M2C_FIELD(M2C_FIELD(temp_s3, void **, 4), s16 *, 8) = (s16) (M2C_FIELD(arg1, u16 *, 0xC) - 1);
    M2C_FIELD(M2C_FIELD(temp_s3, void **, 4), s16 *, 0xA) = (s16) (M2C_FIELD(arg1, u16 *, 0xE) + 1);
}

/* MECHANISM: Model arg2*4 as an integer byte displacement, avoiding scaled-pointer slls.
   Reuse one slot-pointer local across all four regions so gcc holds it in s3.
   That restores the retail s2/s1/s3/s0 hold set and the exact 0x28 frame. */
