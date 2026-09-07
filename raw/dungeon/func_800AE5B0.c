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
extern void *D_80089200[];
s32 func_800981F8();                          /* extern */
s32 func_800A9400();                             /* extern */
extern u8 D_800E3D68;

void func_800B3D10(s16 arg0, s32 arg1, void *arg2) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c6, &&jt_c7, &&jt_c8, &&jt_c12, &&jt_c13, &&jt_c14, &&jt_c15, &&jt_c16, &&jt_c17, &&jt_c18, &&jt_c19, &&jt_c20, &&jt_c21, &&jt_c22, &&jt_c23, &&jt_c30, &&jt_c31, &&jt_c32, &&jt_c33, &&jt_c34, &&jt_c35, &&jt_c36, &&jt_c37, &&jt_c38, &&jt_c39, &&jt_c40, &&jt_c41, &&jt_c42, &&jt_c43, &&jt_c44 };
    s32 temp_v0;
    s32 temp_v1;
    s16 var_v0_2;
    s32 var_a0;
    s32 var_v0_4;
    void *temp_a0;
    void *temp_a0_2;
    void *temp_a0_3;

    temp_v0 = func_800A9400(arg0) - 1;
    temp_v1 = (s16) temp_v0;
    if ((u32) (s32) temp_v1 < 0x31U) {
        (void)jt_keep; goto *D_80089200[(u32) (s32) temp_v1];
    }
    goto block_43;
jt_c0:
{
    s32 result = (s32) (M2C_FIELD(arg2, s16 *, 0x20) * M2C_FIELD(&D_800E3D68, u8 *, 0)) / (s32) (M2C_FIELD(&D_800E3D68, u8 *, 0) + 1);
    s32 flags = M2C_FIELD(arg2, s32 *, 0x14) | 1;
    M2C_FIELD(arg2, s32 *, 0x14) = flags;
    M2C_FIELD(arg2, s16 *, 0x20) = (s16) ((u16) M2C_FIELD(arg2, s16 *, 0x20) + result);
    return;
}
jt_c1:
{
    s32 result = (s32) (M2C_FIELD(arg2, s16 *, 0x20) * M2C_FIELD(&D_800E3D68, u8 *, 0)) / (s32) (M2C_FIELD(&D_800E3D68, u8 *, 0) + 1);
    s32 flags = M2C_FIELD(arg2, s32 *, 0x14) | 2;
    M2C_FIELD(arg2, s32 *, 0x14) = flags;
    M2C_FIELD(arg2, s16 *, 0x20) = (s16) ((u16) M2C_FIELD(arg2, s16 *, 0x20) + result);
    return;
}
jt_c2:
{
    s32 result = (s32) (M2C_FIELD(arg2, s16 *, 0x20) * M2C_FIELD(&D_800E3D68, u8 *, 0)) / (s32) (M2C_FIELD(&D_800E3D68, u8 *, 0) + 1);
    s32 flags = M2C_FIELD(arg2, s32 *, 0x14) | 4;
    M2C_FIELD(arg2, s32 *, 0x14) = flags;
    M2C_FIELD(arg2, s16 *, 0x20) = (s16) ((u16) M2C_FIELD(arg2, s16 *, 0x20) + result);
    return;
}
jt_c6:
    temp_a0 = M2C_FIELD(arg2, void **, 0x4C);
    M2C_FIELD(arg2, s32 *, 0x14) = (s32) (M2C_FIELD(arg2, s32 *, 0x14) | 1);
    if (M2C_FIELD(temp_a0, u8 *, 1) == 0x10) {
        if (M2C_FIELD(temp_a0, u8 *, 0) == 6) {
            M2C_FIELD(arg2, s16 *, 0x20) = (s16) ((u16) M2C_FIELD(arg2, s16 *, 0x20) + ((s32) (M2C_FIELD(arg2, s16 *, 0x20) * M2C_FIELD(&D_800E3D68, u8 *, 0) * 2) / (s32) (M2C_FIELD(&D_800E3D68, u8 *, 0) + 1)));
            return;
        }
        M2C_FIELD(arg2, s16 *, 0x20) = (s16) ((u16) M2C_FIELD(arg2, s16 *, 0x20) + ((s32) (M2C_FIELD(arg2, s16 *, 0x20) * ((*(u8 *)&D_800E3D68) + ((u8) (*(u8 *)&D_800E3D68) >> 1))) / (s32) ((*(u8 *)&D_800E3D68) + 1)));
        return;
    }
    var_a0 = M2C_FIELD(arg2, s16 *, 0x20) - ((s32) (func_800981F8(arg2) << 0x10) >> 0xF);
    if (var_a0 < 0) {
        var_a0 = 0;
    }
    if (M2C_FIELD(M2C_FIELD(arg2, void **, 0x4C), u8 *, 0) == 5) {
        M2C_FIELD(arg2, s16 *, 0x20) = (s16) ((u16) M2C_FIELD(arg2, s16 *, 0x20) + ((var_a0 * (M2C_FIELD(&D_800E3D68, u8 *, 0) + (M2C_FIELD(&D_800E3D68, u8 *, 0) >> 1))) / (s32) (M2C_FIELD(&D_800E3D68, u8 *, 0) + 1)));
    } else {
        M2C_FIELD(arg2, s16 *, 0x20) = (s16) ((u16) M2C_FIELD(arg2, s16 *, 0x20) + ((var_a0 * M2C_FIELD(&D_800E3D68, u8 *, 0)) / (s32) (M2C_FIELD(&D_800E3D68, u8 *, 0) + 1)));
    }
    return;
jt_c7:
    temp_a0_2 = M2C_FIELD(arg2, void **, 0x4C);
    M2C_FIELD(arg2, s32 *, 0x14) = (s32) (M2C_FIELD(arg2, s32 *, 0x14) | 2);
    if (M2C_FIELD(temp_a0_2, u8 *, 1) == 0x10) {
        if (M2C_FIELD(temp_a0_2, u8 *, 0) == 7) {
            M2C_FIELD(arg2, s16 *, 0x20) = (s16) ((u16) M2C_FIELD(arg2, s16 *, 0x20) + ((s32) (M2C_FIELD(arg2, s16 *, 0x20) * M2C_FIELD(&D_800E3D68, u8 *, 0) * 2) / (s32) (M2C_FIELD(&D_800E3D68, u8 *, 0) + 1)));
            return;
        }
        M2C_FIELD(arg2, s16 *, 0x20) = (s16) ((u16) M2C_FIELD(arg2, s16 *, 0x20) + ((s32) (M2C_FIELD(arg2, s16 *, 0x20) * ((*(u8 *)&D_800E3D68) + ((u8) (*(u8 *)&D_800E3D68) >> 1))) / (s32) ((*(u8 *)&D_800E3D68) + 1)));
        return;
    }
    var_a0 = M2C_FIELD(arg2, s16 *, 0x20) - ((s32) (func_800981F8(arg2) << 0x10) >> 0xF);
    if (var_a0 < 0) {
        var_a0 = 0;
    }
    if (M2C_FIELD(M2C_FIELD(arg2, void **, 0x4C), u8 *, 0) == 6) {
        M2C_FIELD(arg2, s16 *, 0x20) = (s16) ((u16) M2C_FIELD(arg2, s16 *, 0x20) + ((var_a0 * (M2C_FIELD(&D_800E3D68, u8 *, 0) + (M2C_FIELD(&D_800E3D68, u8 *, 0) >> 1))) / (s32) (M2C_FIELD(&D_800E3D68, u8 *, 0) + 1)));
    } else {
        M2C_FIELD(arg2, s16 *, 0x20) = (s16) ((u16) M2C_FIELD(arg2, s16 *, 0x20) + ((var_a0 * M2C_FIELD(&D_800E3D68, u8 *, 0)) / (s32) (M2C_FIELD(&D_800E3D68, u8 *, 0) + 1)));
    }
    return;
jt_c8:
    temp_a0_3 = M2C_FIELD(arg2, void **, 0x4C);
    M2C_FIELD(arg2, s32 *, 0x14) = (s32) (M2C_FIELD(arg2, s32 *, 0x14) | 4);
    if (M2C_FIELD(temp_a0_3, u8 *, 1) == 0x10) {
        if (M2C_FIELD(temp_a0_3, u8 *, 0) == 8) {
            M2C_FIELD(arg2, s16 *, 0x20) = (s16) ((u16) M2C_FIELD(arg2, s16 *, 0x20) + ((s32) (M2C_FIELD(arg2, s16 *, 0x20) * M2C_FIELD(&D_800E3D68, u8 *, 0) * 2) / (s32) (M2C_FIELD(&D_800E3D68, u8 *, 0) + 1)));
            return;
        }
        M2C_FIELD(arg2, s16 *, 0x20) = (s16) ((u16) M2C_FIELD(arg2, s16 *, 0x20) + ((s32) (M2C_FIELD(arg2, s16 *, 0x20) * ((*(u8 *)&D_800E3D68) + ((u8) (*(u8 *)&D_800E3D68) >> 1))) / (s32) ((*(u8 *)&D_800E3D68) + 1)));
        return;
    }
    var_a0 = M2C_FIELD(arg2, s16 *, 0x20) - ((s32) (func_800981F8(arg2) << 0x10) >> 0xF);
    if (var_a0 < 0) {
        var_a0 = 0;
    }
    if (M2C_FIELD(M2C_FIELD(arg2, void **, 0x4C), u8 *, 0) == 7) {
        M2C_FIELD(arg2, s16 *, 0x20) = (s16) ((u16) M2C_FIELD(arg2, s16 *, 0x20) + ((var_a0 * (M2C_FIELD(&D_800E3D68, u8 *, 0) + (M2C_FIELD(&D_800E3D68, u8 *, 0) >> 1))) / (s32) (M2C_FIELD(&D_800E3D68, u8 *, 0) + 1)));
    } else {
        M2C_FIELD(arg2, s16 *, 0x20) = (s16) ((u16) M2C_FIELD(arg2, s16 *, 0x20) + ((var_a0 * M2C_FIELD(&D_800E3D68, u8 *, 0)) / (s32) (M2C_FIELD(&D_800E3D68, u8 *, 0) + 1)));
    }
    return;
jt_c12:
jt_c39:
jt_c42:
    M2C_FIELD(arg2, s32 *, 0x14) = M2C_FIELD(arg2, s32 *, 0x14) | 1;
    return;
jt_c13:
jt_c40:
jt_c43:
    M2C_FIELD(arg2, s32 *, 0x14) = M2C_FIELD(arg2, s32 *, 0x14) | 2;
    return;
jt_c15:
jt_c18:
    M2C_FIELD(arg2, s32 *, 0x14) = M2C_FIELD(arg2, s32 *, 0x14) | 1;
    return;
jt_c16:
jt_c19:
    M2C_FIELD(arg2, s32 *, 0x14) = M2C_FIELD(arg2, s32 *, 0x14) | 2;
    return;
jt_c21:
    M2C_FIELD(arg2, s32 *, 0x14) = M2C_FIELD(arg2, s32 *, 0x14) | 1;
    return;
jt_c22:
    M2C_FIELD(arg2, s32 *, 0x14) = M2C_FIELD(arg2, s32 *, 0x14) | 2;
    return;
jt_c30:
jt_c33:
jt_c36:
    M2C_FIELD(arg2, s32 *, 0x14) = M2C_FIELD(arg2, s32 *, 0x14) | 1;
    return;
jt_c31:
jt_c34:
jt_c37:
    M2C_FIELD(arg2, s32 *, 0x14) = M2C_FIELD(arg2, s32 *, 0x14) | 2;
    return;
jt_c14:
jt_c17:
jt_c20:
jt_c23:
jt_c32:
jt_c35:
jt_c38:
jt_c41:
jt_c44:
    var_v0_4 = M2C_FIELD(arg2, s32 *, 0x14) | 4;
block_42:
    M2C_FIELD(arg2, s32 *, 0x14) = var_v0_4;
block_43:
    return;
}
