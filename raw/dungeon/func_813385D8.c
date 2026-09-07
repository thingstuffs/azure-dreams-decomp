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

s32 func_800644B8();                        /* extern */
extern M2C_UNK D_80173DA4;
extern M2C_UNK D_80173DB4;
extern u8 *D_80175D54;

void func_8016F5D8(void *arg0, void *arg1, void *arg2) {
    s32 temp_v1;
    register s32 temp_a0 ASM_REG("$4");
    s32 temp_a1;
    s32 temp_a1_3;
    s32 temp_v1_2;
    s16 signed_count;

    temp_v1 = M2C_FIELD(arg2, s32 *, 0x2C);
    if (temp_v1 == &D_80173DA4) {
        if (M2C_FIELD(arg2, u16 *, 4) == 0x100) {
            M2C_FIELD(arg0, u16 *, 0x9E) = 0U;
            M2C_FIELD(arg0, s32 *, 0xA0) = 0;
        }
        if ((u32) ((u8) M2C_FIELD(arg2, u16 *, 4) - 1) < 4U) {
            temp_v1_2 = M2C_FIELD(arg0, u16 *, 0x9E);
            ASM_KEEP(temp_v1_2);
            signed_count = temp_v1_2;
            temp_a0 = signed_count * 0xAA;
            ASM_USE(temp_a0);
            temp_v1_2++;
            M2C_FIELD(arg0, u16 *, 0x9E) = temp_v1_2;
            M2C_FIELD(arg0, s32 *, 0xA0) += func_800644B8(temp_a0) << 5;
            goto finish;
        }
        temp_v1_2 = M2C_FIELD(arg0, u16 *, 0x9E);
        ASM_KEEP(temp_v1_2);
        signed_count = temp_v1_2;
        temp_a0 = signed_count * 0xAA;
        ASM_USE(temp_a0);
        temp_v1_2++;
        M2C_FIELD(arg0, u16 *, 0x9E) = temp_v1_2;
        M2C_FIELD(arg0, s32 *, 0xA0) += func_800644B8(temp_a0) << 6;
        goto finish;
    }
    if (temp_v1 == &D_80173DB4) {
        if (M2C_FIELD(arg2, u16 *, 4) == 0x100) {
            M2C_FIELD(arg0, u16 *, 0x9E) = 0U;
            M2C_FIELD(arg0, s32 *, 0xA0) = 0;
        }
        if ((u32) ((u8) M2C_FIELD(arg2, u16 *, 4) - 1) < 4U) {
            temp_a1 = M2C_FIELD(arg0, u16 *, 0x9E);
            ASM_KEEP(temp_a1);
            signed_count = temp_a1;
            temp_a0 = signed_count * 0x155;
            ASM_USE(temp_a0);
            temp_a1++;
            M2C_FIELD(arg0, u16 *, 0x9E) = temp_a1;
            M2C_FIELD(arg0, s32 *, 0xA0) += func_800644B8(temp_a0, temp_a1) << 5;
            goto finish;
        }
        temp_a1_3 = M2C_FIELD(arg0, u16 *, 0x9E);
        ASM_KEEP(temp_a1_3);
        signed_count = temp_a1_3;
        temp_a0 = signed_count * 0x155;
        ASM_USE(temp_a0);
        temp_a1_3++;
        M2C_FIELD(arg0, u16 *, 0x9E) = temp_a1_3;
        M2C_FIELD(arg0, s32 *, 0xA0) += func_800644B8(temp_a0) << 6;
    }
finish:
    M2C_FIELD(arg1, s16 *, 0xA) = (s16) ((M2C_FIELD(D_80175D54, u16 *, 0xA8) + M2C_FIELD(arg0, u16 *, 0x92)) - M2C_FIELD(arg0, u16 *, 0xA2));
}

/* MECHANISM: Direct accumulator expressions and one-argument fallback calls recover
   the shared jal/shift/add CFG while arg0/arg1 naturally hold s0/s1 in a 0x20 frame.
   ASM_KEEP preserves each lhu for explicit sign-extension; a guarded $a0 pin plus
   ASM_USE keeps the multiply chain ahead of the in-place counter increment. */
