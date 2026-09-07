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


/* micro-lane E 2026-08-14: true base 0x80024810 (delta 0x7E65D800) */
extern s16 D_80083780[];
extern s32 D_80082E80[];
extern s32 D_800814A0[3];
s32 func_8003DE58();       /* extern */
s32 rand();                                /* extern */

void func_80024810(void *arg0) {
    u16 sp10[3];
    s32 temp_v1_2;
    s32 var_s0;

    void *temp_a0;
    void *temp_v1;

    temp_a0 = M2C_FIELD(arg0, void **, 0);
    temp_v1 = (void *) (M2C_FIELD(arg0, s32 *, 0x34) - 0x20);
    M2C_FIELD(temp_a0, u16 *, 0x52) = (u16) (M2C_FIELD(temp_a0, u16 *, 0x52) | 0x8000);
    M2C_FIELD(arg0, u16 *, 0x24) = (u16) M2C_FIELD(M2C_FIELD(temp_v1, void **, 8), u16 *, 2);
    M2C_FIELD(arg0, u16 *, 0x26) = (u16) M2C_FIELD(M2C_FIELD(temp_v1, void **, 8), u16 *, 6);
    M2C_FIELD(arg0, s16 *, 0x28) = (s16) (M2C_FIELD(M2C_FIELD(temp_v1, void **, 8), u16 *, 0xA) - 0x20);
    M2C_FIELD(arg0, u16 *, 4) = (u16) D_80083780[1];
    M2C_FIELD(arg0, u16 *, 6) = (u16) D_80083780[3];
    M2C_FIELD(arg0, u16 *, 8) = (u16) D_80083780[5];
    if (func_8003DE58(D_80082E80[2], D_80082E80, sp10, 0) != 0) {
        M2C_FIELD(arg0, u16 *, 4) = (u16) (M2C_FIELD(arg0, u16 *, 4) + sp10[0]);
        M2C_FIELD(arg0, u16 *, 6) = (u16) (M2C_FIELD(arg0, u16 *, 6) + sp10[1]);
        M2C_FIELD(arg0, u16 *, 8) = (u16) (M2C_FIELD(arg0, u16 *, 8) + sp10[2]);
    }
    sp10[0] = (u16) ((s32) ((s16) M2C_FIELD(arg0, u16 *, 0x24) - (s16) M2C_FIELD(arg0, u16 *, 4)) >> 2);
    var_s0 = 1;
    sp10[1] = (u16) ((s32) ((s16) M2C_FIELD(arg0, u16 *, 0x26) - (s16) M2C_FIELD(arg0, u16 *, 6)) >> 2);
    sp10[2] = (u16) ((s32) (M2C_FIELD(arg0, s16 *, 0x28) - (s16) M2C_FIELD(arg0, u16 *, 8)) >> 2);
    do {
        M2C_FIELD(arg0, s16 *, (var_s0 * 8) + 4) = (s16) ((M2C_FIELD(arg0, u16 *, 4) + ((s16) sp10[0] * var_s0) + (rand() & 0x3F)) - 0x20);
        M2C_FIELD(arg0, s16 *, (var_s0 * 8) + 6) = (s16) ((M2C_FIELD(arg0, u16 *, 6) + ((s16) sp10[1] * var_s0) + (rand() & 0x3F)) - 0x20);
        M2C_FIELD(arg0, s16 *, (var_s0 * 8) + 8) = (s16) ((M2C_FIELD(arg0, u16 *, 8) + ((s16) sp10[2] * var_s0)) - (rand() & 0x3F));
        var_s0 += 1;
    } while (var_s0 < 4);
    M2C_FIELD(arg0, s16 *, 0x2C) = (s16) (((M2C_FIELD(arg0, u16 *, 0x3E) & 3) << 5) + 0x80);
    M2C_FIELD(arg0, s16 *, 0x2E) = (s16) (((s32) (M2C_FIELD(arg0, u16 *, 0x3E) << 0x10) >> 0x12) << 5);
    temp_v1_2 = M2C_FIELD(arg0, s16 *, 0x3C);
    switch (temp_v1_2) {
    case 0:
        M2C_FIELD(arg0, u16 *, 0x24) = (u16) (M2C_FIELD(arg0, u16 *, 4) + ((s32) ((s16) M2C_FIELD(arg0, u16 *, 0x24) - (s16) M2C_FIELD(arg0, u16 *, 4)) >> 1));
        M2C_FIELD(arg0, u16 *, 0x26) = (u16) (M2C_FIELD(arg0, u16 *, 6) + ((s32) ((s16) M2C_FIELD(arg0, u16 *, 0x26) - (s16) M2C_FIELD(arg0, u16 *, 6)) >> 1));
        M2C_FIELD(arg0, s16 *, 0x28) = (s16) (M2C_FIELD(arg0, u16 *, 8) + ((s32) (M2C_FIELD(arg0, s16 *, 0x28) - (s16) M2C_FIELD(arg0, u16 *, 8)) >> 1));
        M2C_FIELD(arg0, s16 *, 0x3C) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x3C) + 1);
        /* fallthrough */
    case 1:
        if ((s16) M2C_FIELD(arg0, u16 *, 0x3E) >= 6) {
            M2C_FIELD(arg0, u16 *, 0x3E) = 2U;
            M2C_FIELD(arg0, s16 *, 0x3C) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x3C) + 1);
        }
        break;
    case 2:
        if ((s16) M2C_FIELD(arg0, u16 *, 0x3E) >= 8) {
            M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
            D_800814A0[0] = (s32) (D_800814A0[0] | 0x8000);
        }
        break;
    }
    M2C_FIELD(arg0, u16 *, 0x3E) = (u16) (M2C_FIELD(arg0, u16 *, 0x3E) + 1);
}
