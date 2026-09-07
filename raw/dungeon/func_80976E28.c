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

s32 func_800A2BDC();                          /* extern */
M2C_UNK func_800A9A0C();                      /* extern */
s32 func_800ADDA0(); /* extern */
M2C_UNK func_80171C34(); /* extern */
extern u16 D_80083462;

s32 func_80172628(void *arg0, M2C_UNK arg1, M2C_UNK arg2, s32 arg3) {
    s16 temp_v0;
    register s32 var_v0 ASM_REG("$2");
    register M2C_UNK hold_arg1 ASM_REG("$17") = arg1;
    register M2C_UNK hold_arg2 ASM_REG("$18") = arg2;
    register s32 hold_arg3 ASM_REG("$19") = arg3;
    register void *hold_arg0 ASM_REG("$16") = arg0;

    var_v0 = func_800ADDA0(hold_arg1, hold_arg2, hold_arg0, 3, 6, hold_arg0 + 0x9C);
    var_v0 <<= 0x10;
    temp_v0 = var_v0 >> 0x10;
    {
    var_v0 = 0;
    if (temp_v0 < 0) {
        goto done;
    }
    if ((hold_arg3 << 0x10) != 0) {
        goto call_state;
    }
    ASM_KEEP(hold_arg3);
    if (temp_v0 == 1) {
        goto type_one;
    }
    if (temp_v0 >= 2) {
        goto type_ge_two;
    }
    if (temp_v0 == 0) {
        goto type_zero;
    }
    goto reset_state;

type_ge_two:
    if (temp_v0 == 2) {
        goto call_state;
    }
    goto reset_state;

type_zero:
    M2C_FIELD(hold_arg0, s8 *, 0x9A) = 0xE;
    func_800A9A0C(hold_arg0);
    var_v0 = 0;
    goto done;

call_state:
    func_80171C34(hold_arg0, hold_arg1, hold_arg2, hold_arg0);
    ASM_KEEP(hold_arg1);
    ASM_KEEP(hold_arg2);
    var_v0 = 0;
    goto done;

type_one:
    M2C_FIELD(hold_arg0, u8 *, 0x71) = (u8) (M2C_FIELD(hold_arg0, u8 *, 0x71) & 0x7F);
    if ((func_800A2BDC(hold_arg0) << 0x10) != 0) {
        goto clear_state;
    }
reset_state:
    M2C_FIELD(hold_arg0, u8 *, 0x71) = (u8) (M2C_FIELD(hold_arg0, u8 *, 0x71) & 0x7F);
    if ((D_80083462 & 8) == 0) {
        var_v0 = 1;
        goto done;
    }
clear_state:
    var_v0 = 0;
    M2C_FIELD(hold_arg0, u16 *, 0x46) = (u16) (M2C_FIELD(hold_arg0, u16 *, 0x46) & 0x7FFF);
    ASM_KEEP(hold_arg0);
done:
    ASM_KEEP(var_v0);
    return var_v0;
    }
}

/* MECHANISM: The 0x80172714/0x8017274c words are true-space local joins,
   so shared labels replace the seed's phantom calls and preserve retail block order.
   Guarded arg pins fix s1/s2/s3/s0; a v0 return local fills both zero delay slots. */
