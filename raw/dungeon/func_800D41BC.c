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

M2C_UNK func_8003DB94();        /* extern */
s16 func_800A0818();       /* extern */
M2C_UNK func_800A2B04();              /* extern */
M2C_UNK func_800A4ACC();                      /* extern */
M2C_UNK func_800A9A04();                      /* extern */
M2C_UNK func_800AD594();             /* extern */
s32 func_800AD9B4();                  /* extern */
extern M2C_UNK D_80082E80;
extern s16 D_80083228;
extern M2C_UNK D_80083460;
extern M2C_UNK D_800D8C64;
extern void *D_800E262C[];

void func_800D991C(void *arg0, void *arg1, void *arg2, void *arg3) {
    M2C_UNK sp18;
    void **temp_a1;
    s16 *temp_a0_2;
    u8 *temp_v0_4;
    s32 temp_a0;
    s16 temp_v0;
    s32 temp_x;
    s32 temp_x_result;
    s32 temp_y;
    s32 temp_v1_2;
    s32 temp_x_delta;
    s32 temp_y_delta;
    s32 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    switch (temp_v1) {
        case 0:
            M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) | 8);
            M2C_FIELD(arg1, s32 *, 0x14) = 0xFFF00000;
            M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) & 0xF7FFFFFF);
            M2C_FIELD(arg0, s32 *, 0xA4) = 0;
            M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
            break;
        case 1:
            break;
        case 2:
            goto block_13;
        default:
            goto block_17;
    }
block_9:
    temp_a0 = M2C_FIELD(arg0, s16 *, 0x96);
    M2C_FIELD(arg0, s32 *, 0x90) = (s32) (M2C_FIELD(arg0, s32 *, 0x90) - M2C_FIELD(arg0, s32 *, 0xA4));
    if (temp_a0 != 0) {
        temp_x = M2C_FIELD(arg2, u8 *, 0x24) << 6;
        temp_x_delta = M2C_FIELD(arg1, s16 *, 2) - 0x20;
        temp_x_result = (s32) ((temp_x - temp_x_delta) << 0x10) / temp_a0;
        temp_y_delta = M2C_FIELD(arg1, s16 *, 6) - 0x20;
        M2C_FIELD(arg1, s32 *, 0xC) = temp_x_result;
        temp_y = M2C_FIELD(arg2, u8 *, 0x25) << 6;
        M2C_FIELD(arg1, s32 *, 0x10) = (s32) ((s32) ((temp_y - temp_y_delta) << 0x10) / (s16) M2C_FIELD(arg0, s16 *, 0x96));
        M2C_FIELD(arg0, s32 *, 0xA4) = (s32) (M2C_FIELD(arg0, s32 *, 0xA4) + M2C_FIELD(arg1, s32 *, 0x14));
        M2C_FIELD(arg1, s32 *, 0x14) = (s32) (M2C_FIELD(arg1, s32 *, 0x14) + 0x48000);
    }
    M2C_FIELD(arg0, s32 *, 0x90) = (s32) (M2C_FIELD(arg0, s32 *, 0x90) + M2C_FIELD(arg0, s32 *, 0xA4));
    if (M2C_FIELD(arg0, s16 *, 0x96) < 2) {
        M2C_FIELD(arg0, s32 *, 0x90) = 0;
        M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) & 0xFFF7);
        M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) | 0x08000000);
        M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
    }
block_13:
    if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x08000000) {
        M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) & 0xFFF7);
        M2C_FIELD(arg1, s32 *, 0x14) = 0;
        M2C_FIELD(arg1, s32 *, 0x10) = 0;
        M2C_FIELD(arg1, s32 *, 0xC) = 0;
        func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
        temp_a1 = D_800E262C;
        M2C_FIELD(arg2, void **, 0x2C) = temp_a1;
        func_8003DB94(arg2, *(void **)((u8 *)temp_a1 + (((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 7) & 0x1C)), 0);
        M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
    }
block_17:
    temp_v0 = (u16) M2C_FIELD(arg0, s16 *, 0x96) - 1;
    M2C_FIELD(arg0, s16 *, 0x96) = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        M2C_FIELD(arg1, s32 *, 0x14) = 0;
        M2C_FIELD(arg1, s32 *, 0x10) = 0;
        M2C_FIELD(arg1, s32 *, 0xC) = 0;
        func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
        func_800AD594(arg3, 4);
        func_800A4ACC(arg3);
        temp_a0_2 = (s16 *)&D_80083460;
        if (temp_a0_2[4] != 0) {
            temp_a0_2[4] = (s16) ((u16) temp_a0_2[4] - 1);
        }
        temp_v1_2 = M2C_FIELD(arg3, s32 *, 0x1C);
        if (temp_v1_2 & 0x2000) {
            goto block_21;
        }
        if (temp_v1_2 & 0x410) {
            goto block_21;
        }
        if (!(temp_v1_2 & 0x20000)) {
            goto block_21;
        }
        temp_v0_4 = (u8 *)&D_80082E80;
        M2C_FIELD(arg3, s16 *, 0x2A) = func_800A0818(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), temp_v0_4[0x24], temp_v0_4[0x25], &sp18);
block_21:
        if ((func_800AD9B4(arg2, arg3) << 0x10) > 0) {
            M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_800D8C64;
            func_800A9A04(arg3);
        }
    }
}

/* MECHANISM: The true-rowbase natural switch and local gotos preserve the 0x38-frame decision tree.
   Signed full-width loads plus one name per X/Y live range reproduce the mflo-slot load schedule.
   Held symbolic bases and three explicit flag-test edges close the addressing and tail CFG. */
