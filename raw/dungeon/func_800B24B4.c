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

M2C_UNK func_8003DB94();        /* extern */
M2C_UNK func_800478B8();                      /* extern */
extern M2C_UNK D_800814A0;

void func_800B7C14(void *arg0, void *arg1, void *arg2) {
    s32 temp_v1;
    u16 temp_v0_3;
    u8 temp_v0;

    if (M2C_FIELD(arg2, s32 *, 0) != 0) {
        func_800478B8(arg2);
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0x4000) {
            func_8003DB94(arg2, M2C_FIELD(arg0, s32 *, 8), 0);
        }
    }
    M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + M2C_FIELD(arg1, s32 *, 0xC));
    M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) + M2C_FIELD(arg1, s32 *, 0x10));
    temp_v1 = M2C_FIELD(arg1, s32 *, 0xC);
    M2C_FIELD(arg1, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + M2C_FIELD(arg1, s32 *, 0x14));
    M2C_FIELD(arg1, s32 *, 0xC) = (s32) (temp_v1 - (temp_v1 >> 4));
    M2C_FIELD(arg1, s32 *, 0x10) = (s32) (M2C_FIELD(arg1, s32 *, 0x10) - (M2C_FIELD(arg1, s32 *, 0x10) >> 4));
    M2C_FIELD(arg1, s32 *, 0x14) = (s32) (M2C_FIELD(arg1, s32 *, 0x14) + 0x40000);
    if (M2C_FIELD(arg0, s16 *, 0x12) != 0) {
        temp_v0 = M2C_FIELD(arg2, u8 *, 0xC);
        if (temp_v0 != 0) {
            temp_v0 -= 8;
            M2C_FIELD(arg2, u8 *, 0xC) = temp_v0;
            M2C_FIELD(arg2, u8 *, 0xE) = temp_v0;
            M2C_FIELD(arg2, u8 *, 0xD) = temp_v0;
        }
    }
    M2C_FIELD(arg2, u16 *, 0x16) = (u16) (M2C_FIELD(arg2, u16 *, 0x16) + M2C_FIELD(arg0, u16 *, 0x14));
    M2C_FIELD(arg2, u16 *, 0x18) = (u16) (M2C_FIELD(arg2, u16 *, 0x18) + M2C_FIELD(arg0, u16 *, 0x16));
    temp_v0_3 = M2C_FIELD(arg0, u16 *, 0x10) - 1;
    M2C_FIELD(arg0, u16 *, 0x10) = temp_v0_3;
    if ((temp_v0_3 << 0x10) <= 0) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        D_800814A0 = D_800814A0 | 0x8000;
    }
}

/* MECHANISM: Natural argument lifetimes produce the 0x20 frame and s2/s1/s0 held pointers.
   Direct +0x10 field reuse preserves retail's load order and later $a1 damping lifetime.
   One in-place u8 temp gives the branch-delay subtract and three stores the same $v0.
   Direct scalar D_800814A0 RMW removes the extra address-add/displacement cascade. */
