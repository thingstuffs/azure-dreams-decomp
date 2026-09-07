/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
extern u8 D_A0700000[];
extern u8 D_A0700150[];
extern u8 D_A0700158[];
extern u8 D_A0700168[];
extern u8 D_A070017C[];
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

void func_808B3620(s8 *arg0) {
    s8 *base;
    register s8 *held_arg0 ASM_REG("$8") = arg0;
    register s32 *var_a3 ASM_REG("$7") = (s32 *)(D_A0700000 + 0xF40);
    register s32 *var_a2 ASM_REG("$6") = (s32 *)held_arg0;
    register s32 *end ASM_REG("$9") = (s32 *)held_arg0 + 12;
    register s32 temp_v0 ASM_REG("$2");
    register s32 temp_v1 ASM_REG("$3");
    register s32 temp_a0 ASM_REG("$4");
    register s32 temp_a1 ASM_REG("$5");
    ASM_KEEP(held_arg0);

    do {
        ASM_KEEP_NV(var_a3);
        temp_v0 = M2C_FIELD(var_a2, s32 *, 0);
        ASM_KEEP(temp_v0);
        temp_v1 = M2C_FIELD(var_a2, s32 *, 4);
        ASM_KEEP(temp_v1);
        temp_a0 = M2C_FIELD(var_a2, s32 *, 8);
        temp_a1 = M2C_FIELD(var_a2, s32 *, 0xC);
        M2C_FIELD(var_a3, s32 *, 0) = temp_v0;
        M2C_FIELD(var_a3, s32 *, 4) = temp_v1;
        M2C_FIELD(var_a3, s32 *, 8) = temp_a0;
        M2C_FIELD(var_a3, s32 *, 0xC) = temp_a1;
        ASM_SCHED_BARRIER();
        var_a2 += 4;
        ASM_KEEP(var_a2);
        var_a3 += 4;
    } while (var_a2 != end);
    ASM_KEEP_NV(var_a3);
    M2C_FIELD(var_a3, s32 *, 0) = M2C_FIELD(var_a2, s32 *, 0);
    ASM_SCHED_BARRIER();
    base = D_A0700000 + 0x144;
    M2C_FIELD(*(volatile void **)(D_A0700000 + 0xF58), M2C_UNK (**)(u8 *, u8 *, s32, s8 *), 0x64)(base, D_A0700150, M2C_FIELD(held_arg0, s32 *, 8), var_a3);
    M2C_FIELD(*(volatile void **)(D_A0700000 + 0xF58), M2C_UNK (**)(u8 *, u8 *, s32), 0x64)(base, D_A0700158, *(s32 *)(D_A0700000 + 0xF48));
    M2C_FIELD(*(volatile void **)(D_A0700000 + 0xF58), M2C_UNK (**)(u8 *, u8 *, s32), 0x64)(D_A0700168, D_A070017C, 0x30);
    M2C_FIELD(*(volatile void **)(D_A0700000 + 0xF58), M2C_UNK (**)(s32), 0x6C)(0);
}
