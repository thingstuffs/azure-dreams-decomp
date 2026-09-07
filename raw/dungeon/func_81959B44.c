/* cfail-repair: tf7-phase1-cache-v3 */
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

void *func_8003FC64();                       /* extern */
void func_8004491C(void *, void *); /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
extern u8 D_800250B4[];
extern u8 D_80028220[];
extern u8 D_80045C34[];

void *func_81959B44(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    s32 subroutine_arg4;
    s32 subroutine_arg6;
    s32 subroutine_arg8;
    s32 sp28;
    M2C_UNK var_a0;
    s16 temp_s1_2;
    s16 temp_s3_3;
    s32 var_s6;
    s32 temp_lo;
    s32 temp_s1;
    s32 temp_s3;
    s32 temp_s3_2;
    s32 temp_s4;
    s32 temp_v0_2;
    s32 temp_v0_3;
    void *temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_v0;

    var_s6 = 0;
    sp28 = 0x2AAAAAAB;
    do {
        var_a0 = 0x12;
        if (arg3 != 0) {
            var_a0 = 0x212;
        }
        temp_v0 = func_8003FC64(var_a0);
        if (temp_v0 != NULL) {
            M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_800250B4;
            func_8004491C(temp_v0, &D_80045C34);
            temp_s4 = var_s6 << 8;
            temp_s2 = M2C_FIELD(temp_v0, void **, 8);
            temp_s3 = func_80064584(temp_s4) >> 7;
            temp_s3_2 = temp_s3 + ((s32) ((s16) temp_s3 * arg3) >> 2);
            temp_s1 = func_800644B8(temp_s4) >> 7;
            temp_lo = (s16) temp_s1 * arg3;
            temp_s0 = temp_v0 + 0x20;
            temp_s3_3 = arg0 + temp_s3_2;
            M2C_FIELD(temp_s2, s16 *, 2) = temp_s3_3;
            M2C_FIELD(temp_s0, s16 *, 0x1C) = temp_s3_3;
            temp_s1_2 = arg1 + (temp_s1 + (temp_lo >> 2));
            M2C_FIELD(temp_s2, s16 *, 6) = temp_s1_2;
            M2C_FIELD(temp_s0, s16 *, 0x1E) = temp_s1_2;
            M2C_FIELD(temp_s2, s16 *, 0xA) = arg2;
            M2C_FIELD(temp_s0, s16 *, 0x20) = arg2;
            temp_s2_2 = M2C_FIELD(temp_v0, void **, 0xC);
            M2C_FIELD(temp_s2_2, M2C_UNK **, 8) = &D_80028220;
            M2C_FIELD(temp_s2_2, s16 *, 0x1C) = 0x1000;
            M2C_FIELD(temp_s2_2, s16 *, 0x1A) = (u16) (temp_s4 + 0x400);
            temp_v0_2 = 0 - (func_800644B8(temp_s4) << 0xC);
            M2C_FIELD(temp_s2_2, s16 *, 0x16) = (s16) ((temp_v0_2 / 6) >> 0xC);
            temp_v0_3 = func_80064584(temp_s4) << 0xC;
            M2C_FIELD(temp_s2_2, s16 *, 0x18) = (s16) ((temp_v0_3 / 6) >> 0xC);
            M2C_FIELD(temp_s0, s16 *, 0x14) = temp_s3_3;
            M2C_FIELD(temp_s0, s16 *, 0x16) = temp_s1_2;
            M2C_FIELD(temp_s0, s16 *, 0x18) = arg2;
            M2C_FIELD(temp_s0, s16 *, 0x38) = var_s6;
            M2C_FIELD(temp_s0, s16 *, 0x30) = (s16) (arg3 + 4);
            M2C_FIELD(temp_s0, u16 *, 0x3C) = (u16) arg3;
        }
        var_s6 += 1;
    } while (var_s6 < 0x10);
    return temp_v0;
}
