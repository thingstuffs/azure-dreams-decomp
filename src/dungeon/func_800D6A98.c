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

/* cfail-repair: tf7-phase1-cache-v3 */
extern int D_800814A8[4];
s32 func_8004DC14();                    /* extern */
u32 func_80069E98();                             /* extern */
M2C_UNK func_800DBD5C(); /* extern */
M2C_UNK func_800DBE98();                            /* extern */
M2C_UNK func_800DBEE8();                            /* extern */
M2C_UNK func_800DC31C();                     /* extern */
M2C_UNK func_800DC3F0();                            /* extern */
M2C_UNK func_800DC430(); /* extern */
M2C_UNK func_800DC518(); /* extern */

void func_800DC1F8(void *arg0, void *arg1) {
    s32 temp_a0;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v1;
    u16 *temp_v0;
    u16 *temp_v1_3;
    u16 *temp_v1_4;
    u8 temp_a0_3;
    u8 temp_a0_4;
    u8 temp_v0_2;
    u8 temp_v0_3;
    void *temp_a0_2;
    void *temp_a1;
    void *temp_a2;
    void *temp_a3;
    void *temp_s0;
    void *temp_v0_6;
    void *temp_v0_7;
    void *temp_v1_2;
    u8 *page_base;
    void *state = arg1;

    if (M2C_FIELD(arg0, s32 *, 0x18) != 0) {
        temp_v1 = M2C_FIELD(arg0, s32 *, 0x28);
        if (temp_v1 != 1) {
            if (temp_v1 < 2) {
                if (temp_v1 != 0) {
                    func_800DC31C(1);
                    return;
                }
                if ((((u16) *M2C_FIELD(state, u16 **, 8) >> 0xA) & 3) == 1) {
                    func_80053DA8(0x504);
                    M2C_FIELD(arg0, s32 *, 0x20) = (s32) (M2C_FIELD(arg0, s32 *, 0x20) ^ 1);
                    M2C_FIELD(arg0, s32 *, 0x28) = (s32) (M2C_FIELD(arg0, s32 *, 0x28) + 1);
                    M2C_FIELD(arg0, s32 *, 0x24) = (s32) (M2C_FIELD(arg0, s32 *, 0x24) ^ 1);
                }
                goto block_11;
            }
            if (temp_v1 != 2) {
                func_800DC31C(1);
                return;
            }
        if ((((u16) *M2C_FIELD(state, u16 **, 8) >> 0xA) & 3) == 3) {
                func_80053DA8(0x504);
                M2C_FIELD(arg0, s32 *, 0x28) = 0;
                M2C_FIELD(arg0, s32 *, 0x24) = (s32) (M2C_FIELD(arg0, s32 *, 0x24) ^ 1);
                M2C_FIELD(arg0, s32 *, 0x20) = (s32) (M2C_FIELD(arg0, s32 *, 0x20) ^ 1);
            }
            goto block_16;
        }
block_11:
        if ((((u16) *M2C_FIELD(state, u16 **, 8) >> 0xA) & 3) == 2) {
            M2C_FIELD(arg0, s32 *, 0x1C) = 0x10;
            func_800DC31C();
            return;
        }
block_16:
        if (M2C_FIELD(arg0, s32 *, 0x20) != 0) {
            if (M2C_FIELD(arg0, s32 *, 0x24) != 0) {
                func_8004E99C(M2C_FIELD(M2C_FIELD(arg0, void **, 0x3C), s32 *, 0x80));
                func_800DBEE8();
                temp_s0 = M2C_FIELD(arg0, void **, 0x40);
                M2C_FIELD(temp_s0, s16 *, 0x88) = (s16) (((3 - (func_80069E98(M2C_FIELD(arg0, s32 *, 0x2C)) >> 1)) * 6) + 0xA4);
                M2C_FIELD(M2C_FIELD(arg0, void **, 0x3C), s32 *, 0x80) = func_8004DC14(M2C_FIELD(arg0, s32 *, 0x2C), 6);
                if (M2C_FIELD(M2C_FIELD(arg0, void **, 0x3C), s32 *, 0x80) != 0) {
                    func_800DC3F0();
                }
            } else {
                func_8004E99C(M2C_FIELD(M2C_FIELD(arg0, void **, 0x3C), s32 *, 0x80));
                M2C_FIELD(M2C_FIELD(arg0, void **, 0x3C), s32 *, 0x80) = 0;
                M2C_FIELD(arg0, s32 *, 0x10) = 0;
                M2C_FIELD(arg0, s32 *, 0x14) = 0;
                func_800DBE98();
                M2C_FIELD(arg0, s32 *, 0x20) = 0;
                goto block_22;
            }
        } else {
block_22:
            temp_a1 = M2C_FIELD(state, void **, 4);
            temp_a2 = temp_a1;
            temp_a3 = temp_a1;
            temp_v0 = M2C_FIELD(state, u16 **, 8);
            temp_a0 = 0x400 - (((s16) *temp_v0 - 0x400) & 0x7FF);
            if ((*temp_v0 & 0x7FF) < 0x400) {
                func_800DC430(temp_a0, temp_a1, temp_a2, temp_a3);
                return;
            }
            temp_v0_2 = (temp_a0 >> 3) - 0x80;
            M2C_FIELD(temp_a1, u8 *, 2) = temp_v0_2;
            M2C_FIELD(temp_a1, u8 *, 1) = temp_v0_2;
            M2C_FIELD(temp_a1, u8 *, 0) = temp_v0_2;
            temp_a0_2 = M2C_FIELD(state, void **, 4);
            temp_v1_2 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x3C), void **, 0x84);
            temp_v0_3 = M2C_FIELD(temp_a0_2, u8 *, 0);
            M2C_FIELD(temp_v1_2, u8 *, 2) = temp_v0_3;
            M2C_FIELD(temp_v1_2, u8 *, 1) = temp_v0_3;
            M2C_FIELD(temp_v1_2, u8 *, 0) = temp_v0_3;
            temp_v0_4 = M2C_FIELD(arg0, s32 *, 0x1C);
            if (temp_v0_4 == 0) {
                temp_v1_3 = M2C_FIELD(state, u16 **, 8);
                *temp_v1_3 += 0x80;
                temp_v1_4 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x3C), u16 **, 0x88);
                *temp_v1_4 += 0x80;
                temp_v0_5 = M2C_FIELD(arg0, s32 *, 0x18) - 1;
                M2C_FIELD(arg0, s32 *, 0x18) = temp_v0_5;
                if (temp_v0_5 == 0) {
                    M2C_FIELD(arg0, s32 *, 0x28) = 0;
                    *M2C_FIELD(state, u16 **, 8) = 0;
                    *M2C_FIELD(M2C_FIELD(arg0, void **, 0x3C), u16 **, 0x88) = 0x800;
                    temp_v0_6 = M2C_FIELD(state, void **, 4);
                    M2C_FIELD(temp_v0_6, u8 *, 2) = 0x80U;
                    M2C_FIELD(temp_v0_6, u8 *, 1) = 0x80U;
                    M2C_FIELD(temp_v0_6, u8 *, 0) = 0x80U;
                    temp_v0_7 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x3C), void **, 0x84);
                    M2C_FIELD(temp_v0_7, s8 *, 2) = 0x80;
                    M2C_FIELD(temp_v0_7, s8 *, 1) = 0x80;
                    func_800DC518(temp_a0_2, temp_a1, temp_a2, temp_a3);
                    return;
                }
                goto block_30;
            }
            M2C_FIELD(arg0, s32 *, 0x1C) = (s32) (temp_v0_4 - 1);
            goto block_30;
        }
    } else {
block_30:
        if (M2C_FIELD(arg0, s32 *, 0x24) == 0) {
            page_base = (u8 *)0x80080000;
            temp_a0_3 = M2C_FIELD(M2C_FIELD(page_base, s32 *, 0x14A8), u8 *, 0x28);
            if (temp_a0_3 != M2C_FIELD(arg0, s32 *, 0x10)) {
                func_800DBD5C(temp_a0_3, M2C_FIELD(arg0, s32 *, 0x10), 3, 0x1CA, 0x19C, 1);
            }
            temp_a0_4 = M2C_FIELD(M2C_FIELD(page_base, void **, 0x14A8), u8 *, 0x29);
            if (temp_a0_4 != M2C_FIELD(arg0, s32 *, 0x14)) {
                func_800DBC20(temp_a0_4, M2C_FIELD(arg0, s32 *, 0x14), 3, 0x1DA, 0x1A4, 1);
            }
        }
    }
}


