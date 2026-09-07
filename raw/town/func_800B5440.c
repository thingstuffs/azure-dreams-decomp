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

M2C_UNK func_80033D44();                     /* extern */
void *func_8003FC64();                       /* extern */
M2C_UNK func_800A48A4();                     /* extern */
M2C_UNK func_800B2394();             /* extern */
s32 func_800B29D0();                          /* extern */
M2C_UNK func_800B2B60();                      /* extern */
s32 func_800B2C50();                                /* extern */
M2C_UNK func_800B2C6C();                      /* extern */
s32 func_800B3924();                          /* extern */
s32 func_800B4588();                          /* extern */
s32 func_800B4F60();                          /* extern */
extern M2C_UNK D_800B260C;

s32 func_800B2BA0(s32 arg0) {
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    void *temp_s0;
    void *temp_v0;

    temp_v0 = func_8003FC64(0);
    temp_s0 = temp_v0 + 0x20;
    if (temp_v0 == NULL) {
        goto tail;
    }
    func_800B2B60(temp_s0);
    if (func_800B29D0(temp_s0) == 0) {
        goto fail;
    }
    func_800B2394(temp_s0, 0);
    temp_v0_2 = func_800B4588(temp_v0);
    M2C_FIELD(temp_s0, s32 *, 8) = temp_v0_2;
    if (temp_v0_2 == 0) {
        goto fail;
    }
    temp_v0_3 = func_800B3924(temp_v0);
    M2C_FIELD(temp_v0, s32 *, 0x20) = temp_v0_3;
    if (temp_v0_3 == 0) {
        goto fail;
    }
    temp_v0_4 = func_800B4F60(temp_v0);
    M2C_FIELD(temp_s0, s32 *, 4) = temp_v0_4;
    if (temp_v0_4 == 0) {
        goto fail;
    }
    func_800A48A4(5);
    func_80033D44(1);
    M2C_FIELD(temp_s0, s32 *, 0x48) = arg0;
    M2C_FIELD(temp_s0, M2C_UNK **, -0x10) = &D_800B260C;
tail:
    func_800B2C50();
    return (s32)temp_v0;
fail:
    func_800B2C6C(temp_s0);
    return 0;
}

/* MECHANISM: Guard gotos preserve the retail CFG order: success stores, shared
   func_800B2C50 tail, then failure cleanup. The resulting s2/s1/s0 lifetimes
   produce the 0x20 frame and remove the word-38 displacement cascade. */
