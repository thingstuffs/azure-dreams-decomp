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

M2C_UNK func_800419EC();            /* extern */
M2C_UNK func_80047784();         /* extern */
s32 func_800644B8();                             /* extern */
s16 func_800A0818();       /* extern */
M2C_UNK func_800A2B04();              /* extern */
M2C_UNK func_800A4ACC();                      /* extern */
M2C_UNK func_800A9A04();                      /* extern */
M2C_UNK func_800AD594();             /* extern */
s32 func_800AD9B4();                  /* extern */
M2C_UNK func_800B66C8();                      /* extern */
s16 func_800BCB04();                   /* extern */
extern M2C_UNK D_80082E80;
extern s16 D_80083228;
extern M2C_UNK D_80083460;
extern u8 D_8017102C[];
extern u8 D_801752CC[];
extern u8 D_801752D4[];

void func_80172458(void *arg0, void *arg1, void *arg2, void *arg3) {
    M2C_UNK sp18;
    s32 temp_a0;
    s16 temp_v0;
    s16 temp_v1_2;
    s32 temp_v1_3;
    s32 var_v1;
    s16 *global_base;
    u8 *map_base;
    register s32 temp_result ASM_REG("$2");
    register s32 mask_a0 ASM_REG("$4");
    register s32 temp_diff ASM_REG("$3");
    u16 temp_v0_2;
    s32 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    if (temp_v1 == 1) {
        goto block_10;
    }
    if (temp_v1 >= 2) {
        goto state_ge2;
    }
    if (temp_v1 == 0) {
        goto state_zero;
    }
    goto block_36;
state_ge2:
    if (temp_v1 == 2) {
        goto block_34;
    }
    goto block_36;
state_zero:
    if (M2C_FIELD(arg2, u16 *, 0x14) & 0x6000) {
        M2C_FIELD(arg2, u8 **, 0x2C) = D_801752CC;
        func_80047784(arg2, D_801752CC[((D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0);
        M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) | 8);
        M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) & 0xF7FFFFFF);
        M2C_FIELD(arg0, s16 *, 0x9E) = 5;
        M2C_FIELD(arg0, s32 *, 0xA0) = 0;
        M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
        M2C_FIELD(arg0, s16 *, 0xA6) = func_800BCB04((M2C_FIELD(arg2, u8 *, 0x24) << 6) | 0x20, (M2C_FIELD(arg2, u8 *, 0x25) << 6) | 0x20, (s16) (M2C_FIELD(arg3, u16 *, 0x88) - 0x20));
        M2C_FIELD(arg0, u16 *, 0xA8) = (u16) M2C_FIELD(arg1, u16 *, 0xA);
        goto block_10;
    }
    goto block_36;
block_10:
    temp_a0 = M2C_FIELD(arg0, s16 *, 0x9E);
    M2C_FIELD(arg0, s32 *, 0x90) = (s32) (M2C_FIELD(arg0, s32 *, 0x90) - M2C_FIELD(arg0, s32 *, 0xA0));
    if (temp_a0 != 0) {
        temp_result = M2C_FIELD(arg2, u8 *, 0x24);
        temp_diff = M2C_FIELD(arg1, s16 *, 2);
        temp_result <<= 6;
        temp_diff -= 0x20;
        temp_result = ((temp_result - temp_diff) << 0x10) / temp_a0;
        temp_diff = M2C_FIELD(arg1, s16 *, 6);
        M2C_FIELD(arg1, s32 *, 0xC) = temp_result;
        temp_result = M2C_FIELD(arg2, u8 *, 0x25);
        temp_diff -= 0x20;
        temp_result <<= 6;
        temp_result -= temp_diff;
        temp_diff = M2C_FIELD(arg0, s16 *, 0x9E);
        temp_result = (temp_result << 0x10) / temp_diff;
        M2C_FIELD(arg1, s32 *, 0x10) = temp_result;
        if (M2C_FIELD(arg0, s16 *, 0xA4) == 3) {
            M2C_FIELD(arg0, s32 *, 0xA0) = (s32) ((0 - func_800644B8(M2C_FIELD(arg0, s16 *, 0x9E) * 0x155)) << 9);
            M2C_FIELD(arg0, s32 *, 0x90) += M2C_FIELD(arg0, s32 *, 0xA0);
            goto block_32;
        }
        M2C_FIELD(arg1, s32 *, 0x14) = 0;
        temp_v1_2 = M2C_FIELD(arg0, s16 *, 0x9E);
        if (temp_v1_2 == 4) {
            goto case_4;
        }
        if (temp_v1_2 >= 5) {
            goto case_ge5;
        }
        if (temp_v1_2 == 3) {
            goto case_3;
        }
        M2C_FIELD(arg0, s32 *, 0x90) = 0;
        goto block_32;
case_ge5:
        if (temp_v1_2 == 5) {
            goto case_5;
        }
        mask_a0 = 0xF7FF0000;
        if (temp_v1_2 != 6) {
            goto case_default;
        }
        temp_diff = (M2C_FIELD(arg0, s16 *, 0xA6) - (s16) M2C_FIELD(arg0, u16 *, 0xA8)) << 0x10;
        ASM_KEEP(temp_diff);
        temp_result = (s32) (0xFFFE0000 - temp_diff);
        goto mask_flags;
case_5:
        temp_result = (s32) (0 - ((M2C_FIELD(arg0, s16 *, 0xA6) - (s16) M2C_FIELD(arg0, u16 *, 0xA8)) << 0x10));
        mask_a0 = 0xF7FF0000;
mask_flags:
        ASM_KEEP(temp_result);
        M2C_FIELD(arg0, s32 *, 0x90) = temp_result;
        mask_a0 |= 0xFFFF;
        M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) & mask_a0);
        goto block_32;
case_4:
        var_v1 = (M2C_FIELD(arg0, s16 *, 0xA6) - (s16) M2C_FIELD(arg0, u16 *, 0xA8)) * 3;
        if (var_v1 < 0) {
            var_v1 += 3;
        }
        M2C_FIELD(arg0, s32 *, 0x90) = (s32) (0 - ((var_v1 >> 2) << 0x10));
        M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) & 0xF7FFFFFF);
        goto block_32;
case_3:
        M2C_FIELD(arg0, s32 *, 0x90) = (s32) (0 - ((((M2C_FIELD(arg0, s16 *, 0xA6) - (s16) M2C_FIELD(arg0, u16 *, 0xA8)) * 2) / 5) << 0x10));
        goto block_32;
case_default:
        M2C_FIELD(arg0, s32 *, 0x90) = 0;
    }
block_32:
    temp_v0 = (u16) M2C_FIELD(arg0, s16 *, 0x9E) - 1;
    M2C_FIELD(arg0, s16 *, 0x9E) = temp_v0;
    if (temp_v0 < 0) {
        M2C_FIELD(arg0, s32 *, 0x90) = 0;
        M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) & 0xFFF7);
        M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) | 0x08000000);
        M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
    }
block_34:
    if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x08000000) {
        M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) & 0xFFF7);
        M2C_FIELD(arg1, s32 *, 0x14) = 0;
        M2C_FIELD(arg1, s32 *, 0x10) = 0;
        M2C_FIELD(arg1, s32 *, 0xC) = 0;
        func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
        M2C_FIELD(arg2, u8 **, 0x2C) = D_801752D4;
        func_80047784(arg2, D_801752D4[((D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0);
        func_800419EC(4, 8);
        func_800B66C8(arg1);
        M2C_FIELD(arg0, u8 *, 0x9B) = 3U;
    }
block_36:
    temp_v0_2 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
    M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_2;
    if ((temp_v0_2 << 0x10) <= 0) {
        M2C_FIELD(arg1, s32 *, 0x14) = 0;
        M2C_FIELD(arg1, s32 *, 0x10) = 0;
        M2C_FIELD(arg1, s32 *, 0xC) = 0;
        func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
        func_800AD594(arg3, 4);
        func_800A4ACC(arg3);
        global_base = (s16 *)&D_80083460;
        if (global_base[4] != 0) {
            global_base[4] = (s16) ((u16) global_base[4] - 1);
        }
        temp_v1_3 = M2C_FIELD(arg3, s32 *, 0x1C);
        if (temp_v1_3 & 0x2000) {
            temp_v0_2 = M2C_FIELD(arg3, u16 *, 0x46);
            if (temp_v0_2 & 0x8000) {
                M2C_FIELD(arg3, u16 *, 0x46) = temp_v0_2 & 0x7FFF;
            }
            goto block_46;
        }
        if (temp_v1_3 & 0x410) {
            goto block_46;
        }
        if (!(temp_v1_3 & 0x20000)) {
            goto block_46;
        }
        map_base = (u8 *)&D_80082E80;
        M2C_FIELD(arg3, s16 *, 0x2A) = func_800A0818(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), map_base[0x24], map_base[0x25], &sp18);
block_46:
        if ((func_800AD9B4(arg2, arg3) << 0x10) > 0) {
            M2C_FIELD(arg0, u8 **, 0x8C) = D_8017102C;
            func_800A9A04(arg3);
        }
    }
}
