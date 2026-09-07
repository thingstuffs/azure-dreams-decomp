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

s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
s32 func_80065F90();             /* extern */
M2C_UNK func_80095168();                         /* extern */
M2C_UNK func_8009519C();                         /* extern */
extern M2C_UNK D_80000001;

void func_80095094(void *arg0) {
    s32 var_a0;
    s32 var_a1;
    register s32 var_a2 ASM_REG("$6");
    s32 temp_v0;
    register s32 temp_v0_2 ASM_REG("$2");
    register s32 temp_v0_3 ASM_REG("$2");
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v0_6;
    s32 temp_v0_7;
    s32 temp_v0_8;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 var_a0_2;
    s32 var_s0;

    temp_v1 = M2C_FIELD(arg0, s32 *, 0xC);
    if ((temp_v1 != 0) || (M2C_FIELD(arg0, s32 *, 0x10) != 0)) {
        var_a2 = 0x80000001;
        ASM_KEEP(var_a2);
        var_a0 = 0x80000001;
        if (var_a2 < temp_v1) {
            var_a0 = temp_v1;
        }
        temp_v1_2 = M2C_FIELD(arg0, s32 *, 0x10);
        var_a1 = 0x80000001;
        if (var_a2 < temp_v1_2) {
            var_a1 = temp_v1_2;
        }
        var_s0 = func_80065F90(var_a0, var_a1, var_a2);
        temp_v0_2 = func_800644B8(var_s0);
        var_a0_2 = var_s0;
        temp_v0_2 = temp_v0_2 << 5;
        var_s0 = temp_v0_2;
        if (temp_v0_2 < 0) {
            var_s0 = 0 - var_s0;
        }
        ASM_KEEP(temp_v0_2);
        temp_v0_3 = func_80064584(var_a0_2);
        temp_v1_3 = M2C_FIELD(arg0, s32 *, 0xC);
        temp_v0_3 = temp_v0_3 << 5;
        var_a0_2 = temp_v0_3;
        if (temp_v0_3 < 0) {
            var_a0_2 = 0 - var_a0_2;
        }
        ASM_KEEP(temp_v0_3);
        temp_v0_4 = temp_v1_3 - var_s0;
        if (temp_v1_3 < 0) {
            temp_v0_5 = temp_v1_3 + var_s0;
            M2C_FIELD(arg0, s32 *, 0xC) = temp_v0_5;
            if (temp_v0_5 > 0) {
                M2C_FIELD(arg0, s32 *, 0xC) = 0;
                func_80095168(var_a0_2);
                return;
            }
            goto block_16;
        }
        M2C_FIELD(arg0, s32 *, 0xC) = temp_v0_4;
        if (temp_v0_4 < 0) {
            M2C_FIELD(arg0, s32 *, 0xC) = 0;
        }
block_16:
        temp_v0_6 = M2C_FIELD(arg0, s32 *, 0x10);
        if (temp_v0_6 < 0) {
            temp_v0_7 = temp_v0_6 + var_a0_2;
            M2C_FIELD(arg0, s32 *, 0x10) = temp_v0_7;
            if (temp_v0_7 > 0) {
                M2C_FIELD(arg0, s32 *, 0x10) = 0;
                func_8009519C(var_a0_2);
            }
        } else {
            temp_v0_8 = temp_v0_6 - var_a0_2;
            M2C_FIELD(arg0, s32 *, 0x10) = temp_v0_8;
            if (temp_v0_8 < 0) {
                M2C_FIELD(arg0, s32 *, 0x10) = 0;
            }
        }
    }
}

/* MECHANISM: Signed shifted-result lifetimes give the 0x20 frame with s1=arg0 and s0=the held delta.
   Guarded v0 result holds and an a2 sentinel hold reproduce both absolute-value and constant-split slots.
   Explicit field clears before the two sibcalls supply retail's store-filled tail-jump delay slots. */
