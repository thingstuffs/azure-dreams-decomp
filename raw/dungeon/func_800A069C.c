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

M2C_UNK func_800A5F1C();                            /* extern */
M2C_UNK func_800B4C7C(); /* extern */
M2C_UNK func_800C5BBC(); /* extern */

void func_800A5DFC(void *arg0, void *arg1) {
    s32 temp_v1_2;
    s32 var_a2;
    s32 var_s1;
    u8 temp_v1;

    if ((M2C_FIELD(arg0, s32 *, 0x1C) & 0x40) && ((M2C_FIELD(arg0, u8 *, 0x28) + M2C_FIELD(arg0, s16 *, 0x64)) >= 2)) {
        temp_v1 = M2C_FIELD(arg0, u8 *, 0x29);
        var_a2 = temp_v1 + 0xF;
        M2C_FIELD(arg0, s16 *, 0x6A) = (s16) (M2C_FIELD(arg0, u16 *, 0x2A) + 0x800);
        if (var_a2 < 0) {
            var_a2 = temp_v1 + 0x1E;
        }
        var_s1 = var_a2 >> 4;
        temp_v1_2 = M2C_FIELD(arg0, u8 *, 0x28) + M2C_FIELD(arg0, s16 *, 0x64);
        if ((temp_v1_2 - var_s1) <= 0) {
            var_s1 = temp_v1_2 - 1;
        }
        if (var_s1 != 0) {
            M2C_FIELD(arg0, s32 *, 0x1C) = (s32) (M2C_FIELD(arg0, s32 *, 0x1C) & 0xDFFFFFFF);
            if (!(M2C_FIELD(M2C_FIELD(arg0, void **, -0x14), u16 *, 0x14) & 0x8000)) {
                func_800B4C7C(3, arg0, (s16) var_s1, 0);
                M2C_FIELD(arg0, s16 *, 0x64) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x64) - var_s1);
                func_800C5BBC(M2C_FIELD(arg1, s16 *, 2), M2C_FIELD(arg1, s16 *, 6), (s16) (M2C_FIELD(arg1, u16 *, 0xA) - 8), 0x802080, 0x20, 1);
                func_800A5F1C();
                return;
            }
            M2C_FIELD(arg0, u8 *, 0x28) = (u8) (M2C_FIELD(arg0, u8 *, 0x28) - var_s1);
        }
    }
}
