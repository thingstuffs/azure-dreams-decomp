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

M2C_UNK func_800478B8();                      /* extern */
s32 rand();                             /* extern */
extern s32 D_800814A0;

void func_800DB164(void *arg0, void *arg1, void *arg2) {
    s16 temp_v1;
    s32 temp_a0;
    s32 temp_v0;

    temp_v1 = M2C_FIELD(arg0, s16 *, 0x4C);
    temp_a0 = M2C_FIELD(arg0, u16 *, 0x48) - 1;
    M2C_FIELD(arg0, u16 *, 0x48) = temp_a0;
    if (temp_v1 == 1) {
        goto case_1;
    }
    if (temp_v1 >= 2) {
        goto check_2;
    }
    if (temp_v1 == 0) {
        goto case_0;
    }
    goto block_16;

check_2:
    if (temp_v1 == 2) {
        goto case_2;
    }
    goto block_16;

case_0:
    M2C_FIELD(arg2, u16 *, 0x1C) = (u16) (M2C_FIELD(arg2, u16 *, 0x1C) - ((rand(temp_a0) & 0xFF) + 0x300));
    M2C_FIELD(arg2, u16 *, 0x1E) = (u16) (M2C_FIELD(arg2, u16 *, 0x1E) + ((rand() & 0xFF) + 0x200));
    if ((s16) M2C_FIELD(arg0, u16 *, 0x48) > 0) {
        goto block_16;
    }
    temp_v0 = M2C_FIELD(arg0, u16 *, 0x4C) + 1;
    goto store_increment;

case_1:
    M2C_FIELD(arg2, s32 *, 0xC) = (s32) (M2C_FIELD(arg2, s32 *, 0xC) + 0xFFF3F3F4);
    M2C_FIELD(arg1, s32 *, 0x14) = (s32) (M2C_FIELD(arg1, s32 *, 0x14) - ((rand(temp_a0) & 0xFF) << 0xA));
    if (M2C_FIELD(arg1, s16 *, 0xA) < M2C_FIELD(arg0, s16 *, 0x10)) {
        temp_v1 = 4;
        M2C_FIELD(arg0, u16 *, 0x48) = temp_v1;
        temp_v0 = M2C_FIELD(arg0, u16 *, 0x4C) + 1;
        goto store_increment;
    }

    goto block_16;

store_increment:
    M2C_FIELD(arg0, u16 *, 0x4C) = temp_v0;
    goto block_16;

case_2:
    if ((temp_a0 << 0x10) <= 0) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        D_800814A0 |= 0x8000;
    }

block_16:
    if (M2C_FIELD(arg0, s16 *, 0x4C) != 0) {
        M2C_FIELD(arg1, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + M2C_FIELD(arg1, s32 *, 0x14));
        func_800478B8(arg2);
    }
}

/* MECHANISM: The true-space function uses three held argument bases and local CFG joins at
   800DB268/800DB298; restoring the shared increment/store join made the 94-word shape exact.
   Reusing the selector local for constant 4 colored it v1 and preserved the increment in v0. */
