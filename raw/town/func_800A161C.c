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

M2C_UNK func_80033D08();                      /* extern */
M2C_UNK func_8008F134();                      /* extern */
M2C_UNK func_8008F294();             /* extern */
M2C_UNK func_8008F664();             /* extern */
M2C_UNK func_8009539C();                      /* extern */
M2C_UNK func_800A0150(); /* extern */
M2C_UNK func_800C0C88();                            /* extern */
extern s32 D_800814A0[];
typedef struct {
    s32 words[0x15];
} Record84;
extern Record84 D_80100AF8;
extern s32 D_80100B50[];
extern s32 D_80100B68[];

void func_8009ED7C(void *arg0, M2C_UNK arg1, void *arg2) {
    s32 *temp_a0;
    s32 *temp_v1;
    u16 temp_v0;

    temp_a0 = D_80100B50;
    M2C_FIELD(arg2, s32 *, 0xC) = (s32) ((s32) (M2C_FIELD(temp_a0, s32 *, 0) - M2C_FIELD(arg2, s32 *, 0)) / 2);
    M2C_FIELD(arg2, s32 *, 0x10) = (s32) ((s32) (M2C_FIELD(temp_a0, s32 *, 4) - M2C_FIELD(arg2, s32 *, 4)) / 2);
    M2C_FIELD(arg2, s32 *, 0x14) = (s32) ((s32) (M2C_FIELD(temp_a0, s32 *, 8) - M2C_FIELD(arg2, s32 *, 8)) / 2);
    func_8009539C(arg2);
    func_8008F294(arg1, arg2);
    func_8008F664(arg1, arg2);
    temp_v0 = M2C_FIELD(arg0, u16 *, 0x6C) - 1;
    M2C_FIELD(arg0, u16 *, 0x6C) = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        func_800A0150(D_80100B68[0], arg0 + 0x4C, &D_80100AF8, 0);
        func_8008F134(arg0);
        func_80033D08(arg0);
        temp_v0 = M2C_FIELD(arg0, u16 *, -2);
        temp_v1 = D_800814A0;
        M2C_FIELD(arg0, u16 *, -2) = (u16) (temp_v0 | 0x8000);
        *temp_v1 = *temp_v1 | 0x8000;
        func_800C0C88();
    }
}

/* MECHANISM: A named D_80100B50 base carries the three source words in one page register.
   The three arguments remain live in s2/s1/s0 across calls; exact-width halfword updates
   preserve the countdown CFG, while a shared D_800814A0 pointer expresses the tail RMW. */
