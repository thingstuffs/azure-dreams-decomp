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
extern u8 D_80080000[];
extern void func_80024C0C(void) __attribute__((noreturn));

void func_80024B48(void *arg0) {
    s32 temp_v0;
    s32 temp_v1;
    s32 temp_v2;
    s32 temp_v3;

    M2C_FIELD(M2C_FIELD(arg0, void **, 0), u16 *, 0x52) =
        (s16) (M2C_FIELD(M2C_FIELD(arg0, void **, 0), u16 *, 0x52) | 0x8000);
    M2C_FIELD(arg0, u16 *, 0x48) = (u16) (M2C_FIELD(arg0, u16 *, 0x48) + 1);
    if (M2C_FIELD(arg0, s16 *, 0x4C) != 0) {
        if (M2C_FIELD(arg0, s16 *, 0x4C) != 1) {
            func_80024C0C();
            return;
        }
        goto block_5;
    }
    temp_v0 = (s16) M2C_FIELD(arg0, s16 *, 0xC);
    temp_v1 = (s16) M2C_FIELD(arg0, s16 *, 0xE);
    M2C_FIELD(arg0, u16 *, 0x48) = 0U;
    M2C_FIELD(arg0, s16 *, 4) = (s16) ((temp_v0 << 6) + 0x20);
    M2C_FIELD(arg0, s16 *, 6) = (s16) ((temp_v1 << 6) + 0x20);
    temp_v2 = (s16) M2C_FIELD(arg0, s16 *, 0xC);
    temp_v3 = (s16) M2C_FIELD(arg0, s16 *, 0xE);
    M2C_FIELD(arg0, s16 *, 0xC) = (s16) ((temp_v2 - 7) << 6);
    M2C_FIELD(arg0, s16 *, 0xE) = (s16) ((temp_v3 - 7) << 6);
    M2C_FIELD(arg0, s16 *, 0x4C) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x4C) + 1);
block_5:
    if ((s16) M2C_FIELD(arg0, u16 *, 0x48) >= 0x20) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        M2C_FIELD(D_80080000, s32 *, 0x14A0) = (s32) (M2C_FIELD(D_80080000, s32 *, 0x14A0) | 0x8000);
    }
}
