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

s32 func_8004AC3C();                   /* extern */
s32 func_8004DC14();                        /* extern */
M2C_UNK func_800B3290();                            /* extern */

void func_800B3178(void **arg0, void *arg1, s32 arg2) {
    s32 sp10;
    s32 temp_v1;
    s32 var_s2;
    s32 var_s3;
    s32 var_s4;
    s32 var_s5;
    void **var_s0;
    void **var_s1;

    var_s3 = 0;
    var_s5 = 0x40;
    var_s4 = 0x80;
    temp_v1 = M2C_FIELD(arg1, s32 *, 0);
    var_s0 = arg0;
    var_s2 = temp_v1 * 0xA;
    var_s1 = (temp_v1 * 0x28) + arg2;
loop_1:
    if (var_s2 < M2C_FIELD(arg1, s32 *, 0xC)) {
        M2C_FIELD(*var_s0, s32 *, 0) = func_8004DC14(func_8004AC3C(*var_s1, &sp10), sp10);
        if (M2C_FIELD(*var_s1, u8 *, 1) == 0x13) {
            *M2C_FIELD(*var_s0, s8 **, 4) = var_s5;
            M2C_FIELD(M2C_FIELD(*var_s0, s8 **, 4), s8 *, 1) = var_s5;
            M2C_FIELD(M2C_FIELD(*var_s0, s8 **, 4), s8 *, 2) = var_s5;
            func_800B3290();
            return;
        }
        *M2C_FIELD(*var_s0, s8 **, 4) = var_s4;
        M2C_FIELD(M2C_FIELD(*var_s0, s8 **, 4), s8 *, 1) = var_s4;
        M2C_FIELD(M2C_FIELD(*var_s0, s8 **, 4), s8 *, 2) = var_s4;
        ASM_SCHED_BARRIER();
        var_s0 = (void **)((s8 *)((void **)((s8 *)var_s0 + 4)));
        var_s3 += 1;
        var_s1 = (void **)((s8 *)((void **)((s8 *)var_s1 + 4)));
        var_s2 += 1;
        if (var_s3 >= 0xA) {

        } else {
            goto loop_1;
        }
    }
}

/* MECHANISM: Named 0x40/0x80 locals span the loop and force s5/s4, completing the 0x38 hold-set.
   The third 0x40 byte store supplies the tail-j delay slot while arg1 naturally occupies s6.
   ASM_SCHED_BARRIER after the third 0x80 store keeps the four induction updates at the retail tail. */
