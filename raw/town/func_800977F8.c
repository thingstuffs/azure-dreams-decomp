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

typedef struct {
    s32 pad[3];
    s32 first;
    s32 second;
} FuncData;

void func_80094F58(s16 arg0, s32 arg1, FuncData *arg2) {
    s32 first;
    s32 second;
    s32 result;
    s32 condition;
    register s32 rounded_result ASM_REG("$4");
    register s32 adjusted_result ASM_REG("$5");
    register s32 divisor ASM_REG("$3");
    register s32 rounded_arg ASM_REG("$6");
    register s32 first_quotient ASM_REG("$5");
    register s32 second_quotient ASM_REG("$3");

    first = func_800644B8(arg0) << 6;
    second = func_80064584(arg0) << 6;
    arg2->first += first;
    arg2->second += second;
    result = func_8003BD84(arg2->first, arg2->second);
    condition = arg1 < result;
    rounded_result = result + 0xFFF;
    if (condition != 0) {
        adjusted_result = rounded_result;
        if (rounded_result < 0) {
            adjusted_result = result + 0x1FFE;
        }
        divisor = adjusted_result >> 12;
        first_quotient =
            M2C_FIELD(arg2, volatile s32 *, 0xC) / divisor;
        ASM_KEEP(first_quotient);
        rounded_arg = arg1;
        if (arg1 < 0) {
            rounded_arg = arg1 + 0xFFF;
        }
        rounded_arg >>= 12;
        M2C_FIELD(arg2, volatile s32 *, 0xC) =
            first_quotient * rounded_arg;
        second_quotient =
            M2C_FIELD(arg2, volatile s32 *, 0x10) / divisor;
        M2C_FIELD(arg2, volatile s32 *, 0x10) =
            second_quotient * rounded_arg;
    }
}

/* MECHANISM: Typed fields recover the initial v1/a1 update roles.
   A block-local guarded a1 quotient exposes retail's divide/scale live ranges.
   Long-lived args and first shifted result induce the s2/s1/s0 frame contract. */
