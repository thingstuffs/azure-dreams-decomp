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

s32 func_8001709C();                                /* extern */
M2C_UNK func_80017E1C();                            /* extern */
s32 func_80018504();                    /* extern */
s32 func_800194D8();                         /* extern */
extern void *D_80016000;
extern M2C_UNK D_80019AFC;

s32 func_805D2FC4(s32 arg0, M2C_UNK arg1) {
    s32 var_s0;
    u8 temp_v1;

    temp_v1 = M2C_FIELD(((M2C_FIELD(D_80016000, s32 *, 8) * 8) + M2C_FIELD(D_80016000, s32 *, 0x40)), u8 *, 4);
    M2C_FIELD(&D_80019AFC, s32 *, 0) = (s32) temp_v1;
    var_s0 = 0;
    if ((temp_v1 != 2) && (func_800194D8(0x639) != 0)) {
        var_s0 = func_80018504(arg0, arg1);
    }
    if (var_s0 != 0) {
        M2C_FIELD(((M2C_FIELD(D_80016000, s32 *, 8) * 8) + M2C_FIELD(D_80016000, s32 *, 0x40)), s8 *, 4) = 0;
        D_80019AFC = 0;
        return func_8001709C();
    }
    func_80017E1C();
    ASM_KEEP(var_s0);
    if (M2C_FIELD(&D_80019AFC, s32 *, 0) == 1) {
        M2C_FIELD(((M2C_FIELD(D_80016000, s32 *, 8) * 8) + M2C_FIELD(D_80016000, s32 *, 0x40)), s8 *, 4) = 0;
        D_80019AFC = 0;
    }
    return var_s0;
}

/* MECHANISM: The retail prologue is driven by arg0/arg1 held in s1/s2 and
   the conditional helper result held in s0. A post-call read/write liveness
   barrier preserves s0 across the zero-edge; both cleanup arms clear state. */
