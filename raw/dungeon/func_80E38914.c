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
M2C_UNK func_801716A4(); /* extern */
extern u16 D_80083462;

s32 func_80172114(void *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    register M2C_UNK held_arg1 ASM_REG("$17");
    register M2C_UNK held_arg2 ASM_REG("$18");
    register void *held_arg0 ASM_REG("$16");
    register s32 call_result ASM_REG("$2");
    register s32 state ASM_REG("$3");

    held_arg1 = arg1;
    held_arg2 = arg2;
    held_arg0 = arg0;
    call_result = func_800ADDA0(held_arg1, held_arg2, held_arg0, 2, 4, held_arg0 + 0x9C);
    ASM_KEEP(held_arg1);
    ASM_KEEP(held_arg2);
    ASM_KEEP(held_arg0);
    call_result <<= 16;
    state = call_result >> 16;
    call_result = 0;
    if (state < 0) {
        goto negative_return;
    }
    ASM_KEEP(call_result);
    if (state == 1) {
        goto state_one;
    }
    if (state >= 2) {
        goto state_ge_two;
    }
    if (state == 0) {
        goto state_zero;
    }
    goto common_update;

state_ge_two:
    if (state == 2) {
        goto state_two;
    }

    goto common_update;

state_zero:
    M2C_FIELD(held_arg0, s8 *, 0x9A) = 0xE;
    func_800A9A0C(held_arg0);
    return 0;

state_two:
    func_801716A4(held_arg0, held_arg1, held_arg2, held_arg0);
    return 0;

state_one:
    M2C_FIELD(held_arg0, u8 *, 0x71) =
        (u8) (M2C_FIELD(held_arg0, u8 *, 0x71) & 0x7F);
    if ((func_800A2BDC(held_arg0) << 0x10) != 0) {
        goto clear_field;
    }

common_update:
    M2C_FIELD(held_arg0, u8 *, 0x71) =
        (u8) (M2C_FIELD(held_arg0, u8 *, 0x71) & 0x7F);
    if ((D_80083462 & 8) == 0) {
        return 1;
    }

clear_field:
    call_result = 0;
    M2C_FIELD(held_arg0, u16 *, 0x46) =
        (u16) (M2C_FIELD(held_arg0, u16 *, 0x46) & 0x7FFF);

negative_return:
    return call_result;
}

/* MECHANISM: Fixed s1/s2/s0 argument roles reproduce the 0x28 prologue save order.
   The raw call result stays in v0, sign-extends into v1, then v0 becomes the zero edge value.
   Local true-space CFG labels merge the negative and clear-field paths at one epilogue. */
