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

s32 func_80042900();                 /* extern */
M2C_UNK func_8009A028();                      /* extern */
M2C_UNK func_8009A3D0();             /* extern */
void func_800A32A4(void *);                 /* extern */
M2C_UNK func_800A56C0();                            /* extern */
M2C_UNK func_800A56E0();                     /* extern */
void func_800D36B4(s32);                     /* extern */
extern M2C_UNK D_800814A0;
extern M2C_UNK D_80083460;
extern s16 D_8008346A;

void func_800D34CC(void *arg0, void *arg1, void *arg2, void *arg3) {
    M2C_UNK *var_v0;
    M2C_UNK var_a2;
    register s32 temp_a0 ASM_REG("$4");
    s16 temp_a1;
    s16 temp_v0_2;
    s32 temp_dim;
    s32 temp_dim2;
    s32 temp_green;
    s32 temp_v1_4;
    u8 temp_a0_2;
    u8 temp_a1_2;
    u8 temp_v0;
    u8 temp_v1;
    u8 temp_v1_2;
    u8 temp_v1_3;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    if (temp_v1 != 0) {
        temp_a0 = 0x20;
        if (temp_v1 != 1) {
            func_800D36B4(temp_a0);
            return;
        }
        goto block_6;
    }
    if (D_8008346A == 0) {
        M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) | 0x10000000);
        func_800A56E0(0x805);
        M2C_FIELD(arg2, s32 *, 0xC) = 0x808080;
        M2C_FIELD(arg0, s16 *, 0x96) = 0x10;
        M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
        ASM_SCHED_BARRIER();
        temp_a0 = 0x20;
block_6:
        ASM_KEEP(temp_a0);
        temp_v1_2 = (u8) M2C_FIELD(arg2, s32 *, 0xC);
        M2C_FIELD(arg2, u8 *, 0xC) = (u8) (temp_v1_2 + ((temp_a0 - temp_v1_2) / (s16) M2C_FIELD(arg0, s16 *, 0x96)));
        temp_v1_3 = M2C_FIELD(arg2, u8 *, 0xD);
        temp_a1 = M2C_FIELD(arg0, s16 *, 0x96);
        temp_green = temp_v1_3 + ((temp_a0 - temp_v1_3) / temp_a1);
        temp_v0 = M2C_FIELD(arg2, volatile u8 *, 0xE);
        M2C_FIELD(arg2, u8 *, 0xD) = (u8) temp_green;
        M2C_FIELD(arg2, u8 *, 0xE) = (u8) (temp_v0 + ((temp_a0 - temp_v0) / (s16) M2C_FIELD(arg0, s16 *, 0x96)));
        temp_dim = M2C_FIELD(arg2, u16 *, 0x1C);
        M2C_FIELD(arg2, u16 *, 0x1C) = (u16) (temp_dim - (temp_dim / (s16) M2C_FIELD(arg0, s16 *, 0x96)));
        temp_dim2 = M2C_FIELD(arg2, u16 *, 0x1E);
        M2C_FIELD(arg2, u16 *, 0x1E) = (u16) (temp_dim2 - (temp_dim2 / (s16) M2C_FIELD(arg0, s16 *, 0x96)));
        temp_v0_2 = (u16) M2C_FIELD(arg0, s16 *, 0x96) - 1;
        M2C_FIELD(arg0, s16 *, 0x96) = temp_v0_2;
        if (((temp_v0_2 << 0x10) <= 0) || ((M2C_FIELD(arg2, u16 *, 0x14) & 0x8000) != 0)) {
            var_v0 = &D_80083460;
            temp_v1_4 = M2C_FIELD(var_v0, s32 *, 0x10);
            if (temp_v1_4 == (arg3 - 0x20)) {
                M2C_FIELD(var_v0, s32 *, 0x10) = (s32) (temp_v1_4 & 0x7FFFFFFF);
            }
            func_800A32A4(arg3);
            if ((func_80042900(arg3, 0x1B) << 0x10) == 0) {
                temp_a0_2 = M2C_FIELD(arg2, u8 *, 0x24);
                temp_a1_2 = M2C_FIELD(arg2, u8 *, 0x25);
                var_a2 = 0x3000;
                if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x2000) {
                    var_a2 = 0x300;
                }
                func_8009A3D0(temp_a0_2, temp_a1_2, var_a2);
            }
            func_8009A028(arg3);
            M2C_FIELD(arg3, u16 *, -2) = (u16) (M2C_FIELD(arg3, u16 *, -2) | 0x8000);
            D_800814A0 |= 0x8000;
            func_800A56C0();
        }
    }
}

/* MECHANISM: The four-argument ABI yields s0=arg0, s1=arg2, and s2=arg3 in the retail 0x20 frame.
   Split byte/halfword RMWs and one held &D_80083460 base reproduce the widths, live ranges, and CFG.
   Naming the final two byte arguments fills the lw delay slot and removes the +1 displacement cascade. */
