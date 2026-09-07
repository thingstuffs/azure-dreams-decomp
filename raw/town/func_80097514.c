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

s32 func_8003BD84();                        /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
s16 func_80094BC8();                        /* extern */
extern u8 D_80083160[];

typedef struct {
    u8 pad[0xC];
    s32 x;
    s32 y;
} Func97514Object;

void func_80094C74(Func97514Object *arg0) {
    u8 *global_base;
    s16 angle;
    s32 delta_x;
    s32 delta_y;
    s32 old_magnitude;
    s32 new_magnitude;

    global_base = D_80083160;
    ASM_KEEP(global_base);
    angle = func_80094BC8(M2C_FIELD(global_base, s32 *, 8), M2C_FIELD(global_base, s16 *, 0xC8));
    if (angle != -1) {
        register s32 rounded_new ASM_REG("$4");
        register s32 adjusted_new ASM_REG("$5");
        register s32 rounded_old ASM_REG("$6");
        register s32 divisor ASM_REG("$3");
        register s32 dividend ASM_REG("$2");
        register s32 quotient ASM_REG("$5");
        register s32 second_quotient ASM_REG("$3");
        register s32 scaled_value ASM_REG("$7");

        delta_x = func_800644B8(angle) << 6;
        delta_y = func_80064584(angle) << 6;
        old_magnitude = func_8003BD84(arg0->x, arg0->y);
        if (old_magnitude <= 0x7FFFF) {
            old_magnitude = 0x80000;
        }
        arg0->x += delta_x;
        arg0->y += delta_y;
        new_magnitude = func_8003BD84(arg0->x, arg0->y);
        if (old_magnitude < new_magnitude) {
            rounded_new = new_magnitude + 0xFFF;
            adjusted_new = rounded_new;
            if (rounded_new < 0) {
                adjusted_new = new_magnitude + 0x1FFE;
            }
            ASM_KEEP(rounded_new);
            ASM_KEEP(adjusted_new);
            divisor = adjusted_new >> 0xC;
            dividend = arg0->x;
            quotient = dividend / divisor;
            ASM_KEEP(divisor);
            ASM_KEEP(dividend);
            ASM_KEEP(quotient);
            rounded_old = old_magnitude;
            if (old_magnitude < 0) {
                rounded_old = old_magnitude + 0xFFF;
            }
            rounded_old >>= 0xC;
            ASM_KEEP(rounded_old);
            scaled_value = quotient * rounded_old;
            ASM_KEEP(scaled_value);
            *(volatile s32 *)&arg0->x = scaled_value;
            dividend = *(volatile s32 *)&arg0->y;
            second_quotient = dividend / divisor;
            ASM_KEEP(dividend);
            ASM_KEEP(second_quotient);
            scaled_value = second_quotient * rounded_old;
            ASM_KEEP(scaled_value);
            arg0->y = scaled_value;
        }
    }
}

/* MECHANISM: A held D_80083160 base, void ABI, and typed x/y compound updates establish the exact frame and saved-register roles.
   Post-call guarded a0/a1/v1/a2/a3 lifetimes reproduce the two signed-rounding divisions and product/store order.
   Paired volatile x-store/y-load preserves the divide-hazard nops; the rebuilt shape selects exact 2.7.2-cdk-G0 codegen. */
