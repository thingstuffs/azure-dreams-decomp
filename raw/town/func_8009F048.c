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

M2C_UNK func_8008F01C();        /* extern */
M2C_UNK func_8008F104();                         /* extern */
M2C_UNK func_8009B218(); /* extern */
M2C_UNK func_8009C818();     /* extern */
extern M2C_UNK D_800D0690;

void func_8009C7A8(void *arg0, M2C_UNK arg1, void *arg2, s32 arg3, s32 arg4, s32 arg5) {
    if (M2C_FIELD(arg0, u8 *, 0x94) != 0) {
        M2C_FIELD(arg2, s32 *, 8) = arg4;
        func_8008F104(arg0, arg1, arg5);
        func_8009C818(arg0, arg1, arg2, 0);
        return;
    }
    M2C_FIELD(arg2, s32 *, 8) = arg3;
    func_8008F01C(arg0, arg1, arg5);
    {
        register void *call_arg0 ASM_REG("$4");
        register M2C_UNK call_arg1 ASM_REG("$5");
        register void *call_arg2 ASM_REG("$6");
        register M2C_UNK *call_arg3 ASM_REG("$7");

        call_arg0 = arg0;
        ASM_KEEP(call_arg0);
        call_arg1 = arg1;
        ASM_KEEP(call_arg1);
        call_arg2 = arg2;
        ASM_KEEP(call_arg2);
        call_arg3 = &D_800D0690;
        ASM_KEEP(call_arg3);
        func_8009B218(call_arg0, call_arg1, call_arg2, call_arg3);
    }
}

/* MECHANISM: Correct callee arities naturally hold arg0/arg1/arg2 in s0/s1/s2
   and reproduce the 0x20 frame plus the jump-shaped func_8009C818 tail.
   Guarded block-local a0-a3 carriers fully materialize &D_800D0690 before
   the final jal, preserving retail's nop delay slot. */
