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

s32 func_80065F90();                        /* extern */
void func_8008CF34(void) __attribute__((noreturn)); /* extern */

s32 func_7FFEF6A8(void *arg0) {
    register s32 temp_a0 ASM_REG("$4");
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v1;
    s32 temp_v1_2;

    if (M2C_FIELD(arg0, s32 *, 0x6C) == 0) {
        return 1;
    }
    if (M2C_FIELD(arg0, s32 *, 0x78) == 0) {
        goto tail_one;
    }
    M2C_FIELD(arg0, s32 *, 0x7C) = func_80065F90(M2C_FIELD(arg0, s16 *, 0x6E), (s16) M2C_FIELD(arg0, s32 *, 0x6C));
    temp_v0 = func_80065F90(M2C_FIELD(arg0, s16 *, 0x7A), (s16) M2C_FIELD(arg0, s32 *, 0x78));
    M2C_FIELD(arg0, s32 *, 0x88) = temp_v0;
    temp_v0_2 = temp_v0 - M2C_FIELD(arg0, s32 *, 0x7C);
    temp_v1 = (0x1000 - temp_v0_2) & 0xFFF;
    M2C_FIELD(arg0, s32 *, 0x98) = temp_v1;
    M2C_FIELD(arg0, s32 *, 0x88) = temp_v0_2;
    if (temp_v1 >= 0x801) {
        return 0;
    }
    if (M2C_FIELD(arg0, s32 *, 0x74) == 0) {
        goto tail_one;
    }
    temp_v0_3 = func_80065F90(M2C_FIELD(arg0, s16 *, 0x76), (s16) M2C_FIELD(arg0, s32 *, 0x74));
    M2C_FIELD(arg0, s32 *, 0x84) = temp_v0_3;
    temp_v0_4 = temp_v0_3 - M2C_FIELD(arg0, s32 *, 0x7C);
    temp_v1_2 = (M2C_FIELD(arg0, s32 *, 0x88) - temp_v0_4) & 0xFFF;
    M2C_FIELD(arg0, s32 *, 0x94) = temp_v1_2;
    M2C_FIELD(arg0, s32 *, 0x84) = temp_v0_4;
    if (temp_v1_2 >= 0x801) {
        return 0;
    }
    if (M2C_FIELD(arg0, s32 *, 0x70) != 0) {
        goto have_field70;
    }
tail_one:
    {
        register s32 rv ASM_REG("$2");
        rv = 1;
        ASM_TAILSLOT_PIN(rv);
        func_8008CF34();
        return rv;
    }
have_field70:
    temp_v0_5 = func_80065F90(M2C_FIELD(arg0, s16 *, 0x72), (s16) M2C_FIELD(arg0, s32 *, 0x70));
    M2C_FIELD(arg0, s32 *, 0x80) = temp_v0_5;
    temp_a0 = (temp_v0_5 - M2C_FIELD(arg0, s32 *, 0x7C)) & 0xFFF;
    M2C_FIELD(arg0, s32 *, 0x80) = temp_a0;
    if (temp_a0 < 0x801) {
        s32 tail_angle;
        register s32 rv ASM_REG("$2");

        tail_angle = (M2C_FIELD(arg0, s32 *, 0x84) - temp_a0) & 0xFFF;
        rv = tail_angle < 0x801;
        ASM_KEEP(rv);
        M2C_FIELD(arg0, s32 *, 0x90) = tail_angle;
        func_8008CF34();
        return rv;
    }
    return 0;
}

/* MECHANISM: A vars=0 24-byte frame follows from one held object base in s0.
   Guard-clause CFGs retain the two move-zero branch slots and exact store order.
   A pinned a0 angle plus v0 tail result reproduces the final register lifetimes.
   Keeping v0 before the field90 store lets that store fill the noreturn tail-j slot. */
