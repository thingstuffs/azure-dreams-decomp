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

M2C_UNK func_8009A028();                         /* extern */
M2C_UNK func_8016E998();                   /* extern */
extern u16 D_80013714;
extern s16 D_80013716;
extern s16 D_80013718;
extern s16 D_8001371A;
extern s32 D_8001371C;
extern s32 D_8008346C;
extern M2C_UNK D_80083780;
extern M2C_UNK D_800E296C;
extern M2C_UNK D_800E3D7C;
extern s32 D_80173C94;
extern s32 D_80173D5C;
extern s32 D_80175D50;
extern s32 D_80175DC4;
extern s16 D_80175DC8;

void func_8016EE8C(void) {
    s32 temp_a0;
    s32 temp_s0;
    s32 var_s1;
    void *temp_a3;
    void *page_8001;
    void *page_800e;
    void *temp_v1;

    var_s1 = 0;
    page_8001 = (void *)0x80010000;
    page_800e = (void *)0x800E0000;
    temp_a3 = D_80175D50 + 0x20;
    M2C_FIELD(temp_a3, s8 *, 0xAF) = 1;
    M2C_FIELD(page_8001, s16 *, 0x371A) = 0;
    M2C_FIELD(page_8001, s16 *, 0x3718) = 0;
    M2C_FIELD(page_8001, s16 *, 0x3716) = 0;
    D_8008346C = 0;
    D_80175DC8 = 0;
    M2C_FIELD(page_800e, s32 *, 0x296C) = (s32) (M2C_FIELD(page_800e, s32 *, 0x296C) | 0x08000000);
    M2C_FIELD(page_8001, u16 *, 0x3714) = (u16) ((M2C_FIELD(page_8001, u16 *, 0x3714) | 9) & 0xFFEF);
    M2C_FIELD(page_8001, s32 *, 0x371C) = (s32) D_80173C94;
    D_80175DC4 = D_80173D5C;
    M2C_FIELD(temp_a3, s8 *, 0xAB) = 0;
    do {
        temp_s0 = var_s1 * 4;
        temp_a0 = M2C_FIELD((temp_s0 + M2C_FIELD(&D_800E3D7C, s32 *, 0)), s32 *, 0xAC);
        if (temp_a0 != 0) {
            func_8009A028(temp_a0);
            temp_v1 = M2C_FIELD((temp_s0 + M2C_FIELD(&D_800E3D7C, s32 *, 0)), s32 *, 0xAC) - 0x20;
            M2C_FIELD(temp_v1, s32 *, 0x10) = (s32) (M2C_FIELD(temp_v1, s32 *, 0x10) | 0x80000000);
        }
        var_s1 += 1;
    } while (var_s1 < 2);
    func_8016E998(&D_80083780);
}

/* MECHANISM: A 40-byte frame falls out naturally from s0-s3: s2 holds the
   relocatable D_800E3D7C page across calls, while s3 holds 0x80000000.
   Short-lived 0x80010000/0x800E0000 page locals preserve direct displacements
   and avoid the extra address-add/register hold that caused the residue. */
