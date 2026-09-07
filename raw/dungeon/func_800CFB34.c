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
extern s32 D_800814A0[3];
extern u16 D_80083460[];
void *func_8003FC64();                       /* extern */
s32 rand();                                /* extern */
M2C_UNK func_800D4BD4(); /* extern */
extern M2C_UNK D_800D50FC[3];

void func_800D5294(void *arg0, void *arg1, M2C_UNK arg2) {
    s32 var_s1;
    u16 temp_v0;
    u16 temp_v0_4;
    s16 temp_v1;
    s16 temp_s3;
    void *temp_a0;
    void *temp_s0;
    u16 *fixed;
    M2C_UNK *temp_s5;
    void *temp_v0_2;
    void *temp_v0_3;

    temp_a0 = M2C_FIELD(arg0, void **, 0x24);
    M2C_FIELD(arg1, s16 *, 2) = (s16) (M2C_FIELD(M2C_FIELD(temp_a0, void **, 8), u16 *, 2) + M2C_FIELD(arg0, u16 *, 0x3C));
    M2C_FIELD(arg1, s16 *, 6) = (s16) (M2C_FIELD(M2C_FIELD(temp_a0, void **, 8), u16 *, 6) + M2C_FIELD(arg0, u16 *, 0x3E));
    M2C_FIELD(arg1, s16 *, 0xA) = (s16) (M2C_FIELD(M2C_FIELD(temp_a0, void **, 8), u16 *, 0xA) + M2C_FIELD(arg0, u16 *, 0x40));
    temp_v0 = M2C_FIELD(arg0, u16 *, 0x16) + 1;
    M2C_FIELD(arg0, u16 *, 0x16) = temp_v0;
    if ((s16) temp_v0 < 0x14) {
        var_s1 = 0;
        temp_s3 = 0x20;
        temp_s5 = D_800D50FC;
        do {
            temp_v0_2 = func_8003FC64(0x212);
            if (temp_v0_2 != NULL) {
                func_800D4BD4(temp_v0_2, arg0, arg1, arg2);
                temp_v0_3 = temp_v0_2 + 0x20;
                M2C_FIELD(temp_v0_3, s16 *, 0x1E) = temp_s3;
                M2C_FIELD(temp_v0_3, s16 *, 0x20) = temp_s3;
                M2C_FIELD(temp_v0_2, M2C_UNK **, 0x10) = temp_s5;
                temp_s0 = M2C_FIELD(temp_v0_2, void **, 8);
                temp_v0 = rand() & 0x3F;
                temp_v1 = M2C_FIELD(temp_s0, s16 *, 2);
                temp_v1 = temp_v1 - 0x1F;
                M2C_FIELD(temp_s0, s16 *, 2) = temp_v1 + temp_v0;
                temp_v0 = rand() & 0x3F;
                temp_v1 = M2C_FIELD(temp_s0, s16 *, 6);
                temp_v1 = temp_v1 - 0x1F;
                M2C_FIELD(temp_s0, s16 *, 6) = temp_v1 + temp_v0;
                temp_v0 = rand() & 0x1F;
                M2C_FIELD(temp_s0, s16 *, 0xA) = (s16) (M2C_FIELD(temp_s0, s16 *, 0xA) - temp_v0);
                M2C_FIELD(temp_s0, s32 *, 0x14) = (s32) ((0 - ((rand() & 0xFFFF) + 0x10000)) * 2);
            }
            var_s1 += 1;
        } while (var_s1 < 4);
    }
    temp_v0_4 = M2C_FIELD(arg0, u16 *, 0x1E) - 1;
    M2C_FIELD(arg0, u16 *, 0x1E) = temp_v0_4;
    if ((temp_v0_4 << 0x10) <= 0) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        D_800814A0[0] = D_800814A0[0] | 0x8000;
        fixed = D_80083460;
        fixed[5] = fixed[5] - 1;
    }
}
