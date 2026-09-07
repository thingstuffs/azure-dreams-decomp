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

M2C_UNK func_80047784();         /* extern */
M2C_UNK func_8009C93C(); /* extern */
s32 func_800A0134();                     /* extern */
s32 func_800A04F0();             /* extern */
s32 func_800A2B5C();                          /* extern */
s32 func_800A2CB8();                     /* extern */
M2C_UNK func_800C7930(); /* extern */
s32 func_80171F9C();                                /* extern */
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_80174F28;

s32 func_80171E00(void *arg0, M2C_UNK arg1, void *arg2, void *arg3) {
    volatile s64 frame_pad;
    u8 *flags_base;
    u8 *table;
    s32 temp_v0;
    u16 flags;

    M2C_FIELD(arg3, u8 *, 0x71) = (u8) (M2C_FIELD(arg3, u8 *, 0x71) & 0x7F);
    flags_base = (u8 *) &D_80083460;
    if (M2C_FIELD(flags_base, u16 *, 2) & 0x2000) {
        goto return_minus_one;
    }
    temp_v0 = func_800A04F0(arg3, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), M2C_FIELD(arg3, s16 *, 0x2A));
    if ((func_800A2CB8(arg3, temp_v0) << 0x10) == 0) {
        return 0;
    }
    flags = M2C_FIELD(flags_base, u16 *, 2);
    if (flags & 0x2000) {
        return -1;
    }
    if (!(M2C_FIELD(arg3, u16 *, 0x46) & 0x8000)) {
        if (flags & 8) {
            return -1;
        }
    }
    if ((u32) (((0 - func_800A0134(temp_v0, arg3)) + 0x3F) & 0xFFFF) >= 0x7FU) {
        return 0;
    }
    if ((func_800A2B5C(arg3) << 0x10) != 0) {
        return -1;
    }
    func_800C7930(arg3 - 0x20, arg1, 8, 0x300);
    if ((func_800A2B5C(arg3) << 0x10) == 0) {
        goto success;
    }
return_minus_one:
    return -1;
success:
    M2C_FIELD(arg0, s8 *, 0x9A) = 0x11;
    M2C_FIELD(arg0, s8 *, 0x9B) = 0;
    M2C_FIELD(arg0, s32 *, 0x8C) = 0;
    M2C_FIELD(arg3, s8 *, 0x84) = 0x7C;
    M2C_FIELD(arg3, s8 *, 0x85) = 0;
    table = &D_80174F28;
    M2C_FIELD(arg2, u8 **, 0x2C) = table;
    func_80047784(arg2, table[((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0);
    M2C_FIELD(arg3, u8 *, 0x6D) = (u8) (M2C_FIELD(arg3, u8 *, 0x6D) - 1);
    func_8009C93C(arg3, arg2, M2C_FIELD(arg3, s16 *, 0x2A), 1, 0);
    return 1;
}

/* MECHANISM: A volatile s64 frame object yields the retail 0x40 frame and exact save offsets.
   At cdk-G0, natural C holds &D_80083460 in s2; depinning removes the prologue and call-result rotations.
   The explicit failure/success CFG plus u8 table indexing reproduces the retail tail widths and order. */
