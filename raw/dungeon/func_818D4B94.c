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

void *func_8003FD64();               /* extern */
M2C_UNK func_8004491C();      /* extern */
extern M2C_UNK D_80024044;
extern M2C_UNK D_80024294;

void func_818D4B94(void *arg0, s16 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    register s16 held_arg1 ASM_REG("$22") = arg1;
    register s32 held_arg2 ASM_REG("$23") = arg2;
    register s32 held_arg3 ASM_REG("$21") = arg3;
    register s32 held_arg4 ASM_REG("$18") = arg4;
    register s32 held_arg5 ASM_REG("$19") = arg5;
    register s32 held_arg6 ASM_REG("$20") = arg6;
    s32 signed_arg3;
    s32 var_v1;
    s32 temp_a1;
    s32 numerator;
    s32 temp_lo;
    s32 temp_lo_2;
    s32 var_v1_2;
    void *temp_s0;
    void *temp_v0;

    temp_v0 = func_8003FD64(0x211, arg0);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_80024294;
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s16 *, 2) = (s16) (M2C_FIELD(M2C_FIELD(arg0, void **, 8), u16 *, 2) + held_arg4);
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s16 *, 6) = (s16) (M2C_FIELD(M2C_FIELD(arg0, void **, 8), u16 *, 6) + held_arg5);
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s16 *, 0xA) = (s16) (M2C_FIELD(M2C_FIELD(arg0, void **, 8), u16 *, 0xA) + held_arg6);
        temp_s0 = temp_v0 + 0x20;
        M2C_FIELD(temp_s0, u16 *, 0x34) = (u16) M2C_FIELD(M2C_FIELD(arg0, void **, 8), u16 *, 2);
        M2C_FIELD(temp_s0, u16 *, 0x36) = (u16) M2C_FIELD(M2C_FIELD(arg0, void **, 8), u16 *, 6);
        M2C_FIELD(temp_s0, u16 *, 0x38) = (u16) M2C_FIELD(M2C_FIELD(arg0, void **, 8), u16 *, 0xA);
        signed_arg3 = (s16) held_arg3;
        var_v1 = signed_arg3;
        numerator = 0 - (held_arg4 << 0x10);
        if (signed_arg3 < 0) {
            var_v1 = signed_arg3 + 7;
        }
        temp_a1 = var_v1 >> 3;
        temp_lo = numerator / temp_a1;
        if (temp_lo < 0) {
            temp_lo += 0xF;
        }
        M2C_FIELD(temp_s0, s32 *, 0x48) = temp_lo >> 4;
        ASM_KEEP(held_arg4);
        temp_lo_2 = (s32) (0 - (held_arg5 << 0x10)) / temp_a1;
        if (temp_lo_2 < 0) {
            temp_lo_2 += 0xF;
        }
        M2C_FIELD(temp_s0, s32 *, 0x4C) = temp_lo_2 >> 4;
        ASM_KEEP(held_arg5);
        ASM_KEEP(held_arg1);
        ASM_KEEP(held_arg3);
        ASM_KEEP(held_arg2);
        var_v1_2 = (s32) (0 - (held_arg6 << 0x10)) / temp_a1;
        if (var_v1_2 < 0) {
            var_v1_2 += 0xF;
        }
        M2C_FIELD(temp_s0, s32 *, 0x50) = (s32) (var_v1_2 >> 4);
        M2C_FIELD(temp_s0, s16 *, 0x14) = held_arg1;
        M2C_FIELD(temp_s0, s16 *, 0x32) = held_arg3;
        func_8004491C(temp_v0, &D_80024044, signed_arg3);
        ASM_KEEP(held_arg6);
        M2C_FIELD(temp_s0, s32 *, 8) = held_arg2;
    }
}

/* MECHANISM: Exact 0x38 frame with raw arguments pinned to retail's s1-s7 roles.
   A raw s32 arg3 plus signed s16 local, mutable quotient locals, and pre-branch numerator reproduce the CFG.
   Keep seams before division and after the call preserve s4 while allowing the global address delay-slot hoist. */
