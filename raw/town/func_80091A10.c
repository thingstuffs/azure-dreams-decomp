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

s16 func_8008C758(); /* extern */
s16 func_8008CF48();                    /* extern */
extern M2C_UNK D_800CFD18;

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
} Unk80091A10;

s32 func_8008F170(void *arg0, s32 *arg1) {
    Unk80091A10 sp18;
    s32 sp30;
    s16 temp_v0;
    s16 var_s2;

    sp18.unk0 = M2C_FIELD(arg0, s32 *, 0);
    sp18.unk4 = M2C_FIELD(arg0, s32 *, 4);
    sp18.unk8 = M2C_FIELD(arg0, s32 *, 8) - M2C_FIELD(arg0, s32 *, 0x14);
    var_s2 = func_8008CF48(&sp18, &sp30);
    *arg1 = sp30;
    sp18.unk0 = M2C_FIELD(arg0, s32 *, 0);
    sp18.unk4 = M2C_FIELD(arg0, s32 *, 4);
    sp18.unk8 = M2C_FIELD(arg0, s32 *, 8) - M2C_FIELD(arg0, s32 *, 0x14);
    temp_v0 = func_8008C758(&sp18, &D_800CFD18, 4, &sp30, (s32) var_s2, *arg1);
    if (temp_v0 < var_s2) {
        var_s2 = temp_v0;
        *arg1 = sp30;
    }
    if (var_s2 >= 0x80) {
        var_s2 = 0x80;
    }
    return var_s2;
}

/* MECHANISM: A 24-byte escaped record plus the separate sp30 output force the retail
   0x50 frame, stack offsets, and complete six-store copy sequence. Direct s16 CFG
   expressions remove shifted-temporary residue; 2.7.2-cdk-G0 supplies the exact schedule. */
