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

M2C_UNK func_80041284();                   /* extern */
s32 func_80048D00();                                /* extern */
M2C_UNK bzero();          /* extern */
extern s32 D_80012D60;
extern s32 D_80080A80;
extern M2C_UNK *D_80080A90;
extern M2C_UNK D_80080AE0;
extern M2C_UNK D_80080AE8;
extern M2C_UNK D_80080E18;
extern M2C_UNK D_80080E20;
extern M2C_UNK D_80080E30;
extern M2C_UNK D_80080EE8;
extern s16 D_80081468[3];
extern u8 D_80082E6B;
extern M2C_UNK D_80083460;
extern s16 D_800DCE68;
extern M2C_UNK D_800DCF4E;
extern s8 D_800DCF4F;
extern s8 D_800DCF58;
extern s8 D_800DCF5B;
extern s32 D_800E296C;
extern M2C_UNK D_800E3548;
extern M2C_UNK D_800E36C8;
extern s16 D_800E3CCC;
extern s16 D_800E3CCE;
extern s32 D_800E3D70;
extern s8 D_800E3E40;
extern M2C_UNK D_8014A000;

void func_8001625C(void) {
    M2C_UNK *state;
    M2C_UNK *var_s0;
    s16 *temp_v1;
    s32 *temp_v0;

    bzero(&D_800E3548, 0x100);
    bzero(&D_800E36C8, 0x300);
    state = &D_80083460;
    M2C_FIELD(state, s16 *, 8) = 0;
    M2C_FIELD(state, s16 *, 0xA) = 0;
    M2C_FIELD(state, s16 *, 0x14) = 0;
    M2C_FIELD(state, s32 *, 0xC) = 0;
    M2C_FIELD(state, s32 *, 0x10) = 0;
    M2C_FIELD(&D_80083460, s16 *, 0) = 0x100;
    M2C_FIELD(state, s16 *, 2) = 0;
    M2C_FIELD(state, s16 *, 0x1C) = 0;
    M2C_FIELD(state, s16 *, 4) = 0;
    D_800DCE68 = 0;
    D_800E3E40 = 0;
    D_800E296C = 0;
    D_800E3CCC = 0;
    D_800E3CCE = 0;
    D_800DCF4F = 0;
    D_80080A90 = &D_8014A000;
    D_800E3D70 = 0;
    temp_v0 = &D_800E3D70;
    M2C_FIELD(temp_v0, s32 *, 4) = 0;
    M2C_FIELD(temp_v0, s32 *, 8) = 0;
    D_800DCF58 = 1;
    D_800DCF5B = 0;
    if (D_80082E6B != 5) {
        temp_v1 = D_80081468;
        if (temp_v1[2] >= 0x64) {
            temp_v1[2] = 0x63;
        }
        var_s0 = (M2C_UNK *)0x800E0000;
        if ((u32) D_80012D60 < (u32) temp_v1[2]) {
            D_80012D60 = (s32) temp_v1[2];
            goto block_5;
        }
    } else {
block_5:
        var_s0 = (M2C_UNK *)0x800E0000;
    }
    if (M2C_FIELD(var_s0, s8 *, -0x30B2) == 0) {
        func_80041284(&D_80080AE0);
        func_80041284(&D_80080AE8);
        func_80041284(&D_80080E18);
        func_80041284(&D_80080E20);
        func_80041284(&D_80080EE8);
        func_80041284(&D_80080E30);
        D_80080A80 = func_80048D00();
        M2C_FIELD(var_s0, s8 *, -0x30B2) = 1;
    }
}

/* MECHANISM: Named D_80083460 and D_80081468 bases reproduce the retail held-address forms.
   D_800E3D70 and D_80012D60 use their symbol addresses without duplicated byte displacements.
   Holding the 0x800E0000 page in s0 removes one addiu and closes the branch-displacement cascade. */
