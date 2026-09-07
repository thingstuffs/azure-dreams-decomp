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

s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
s32 rand();                                /* extern */
M2C_UNK func_800ABC00(void *, s16);              /* extern */

typedef struct {
    s16 unk0;
    s16 x;
    s16 unk4;
    s16 y;
    s16 unk8;
    u16 z;
    s32 a;
    s32 b;
    s16 unk14;
    s16 c;
} StackRecord;

void func_800ABD74(void *arg0) {
    register void *base ASM_REG("$19");
    StackRecord sp10;
    s32 var_s0;
    register s32 temp_s2 ASM_REG("$18");
    s32 temp_s4;
    s32 var_s1;

    base = arg0;
    temp_s2 = (rand() & 7) | 4;
    temp_s4 = 0x1000 / temp_s2;
    var_s1 = 0;
    var_s0 = rand();
    ASM_KEEP(var_s0);
    ASM_KEEP(temp_s2);
    sp10.z = M2C_FIELD(base, u16 *, 0xA);
    sp10.c = -4;
    if (temp_s2 != 0) {
        do {
            var_s1 += 1;
            sp10.x = (M2C_FIELD(base, u16 *, 2) + (rand() & 0x1F)) - 0x10;
            sp10.y = (M2C_FIELD(base, u16 *, 6) + (rand() & 0x1F)) - 0x10;
            sp10.a = func_80064584(var_s0) << 5;
            sp10.b = func_800644B8(var_s0) << 5;
            func_800ABC00(&sp10, var_s0);
            var_s0 += temp_s4;
        } while (var_s1 < temp_s2);
    }
    ASM_KEEP(base);
}

/* MECHANISM: One 24-byte stack record reproduces the overlapping sp+0x10 fields and 0x40 frame.
   The base pin holds arg0 in s3; the s2 pin/early keeps retain the otherwise-folded beqz.
   The s16 callee ABI and load-before--4-store order close the tail and its delay slot. */
