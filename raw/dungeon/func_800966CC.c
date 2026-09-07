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
struct S_8003E2D8; typedef struct S_8003E2D8 S_8003E2D8;
extern struct S_8003E2D8 D_80083160;
extern s32 D_800814A0[3];
M2C_UNK func_8006658C();              /* extern */
M2C_UNK func_800667A8();                  /* extern */

void func_8009BE2C(void *arg0, s32 arg1, void *arg2) {
    s32 temp_lo;
    s16 temp_v1;
    s8 temp_v0;
    void *temp_s0;
    void **temp_s1;

    temp_s0 = M2C_FIELD(M2C_FIELD(&D_80083160, void **, 0), void **, 0x8D0);
    M2C_FIELD(M2C_FIELD(&D_80083160, void **, 0), void **, 0x8D0) = (void *) (temp_s0 + 0x10);
    M2C_FIELD(temp_s0, s16 *, 0xC) = 0x140;
    M2C_FIELD(temp_s0, s16 *, 8) = 0;
    M2C_FIELD(temp_s0, s16 *, 0xA) = 0;
    M2C_FIELD(temp_s0, s16 *, 0xE) = 0xE0;
    temp_lo = (0xC0 / (s16) M2C_FIELD(arg2, s16 *, 6)) * M2C_FIELD(arg2, s8 *, 5);
    temp_v1 = temp_lo;
    temp_s1 = (void **)&D_80083160;
    if (M2C_FIELD(arg2, s8 *, 4) == 0) {
        goto set_word;
    }
    M2C_FIELD(temp_s0, s8 *, 6) = temp_v1;
    M2C_FIELD(temp_s0, s8 *, 5) = temp_v1;
    M2C_FIELD(temp_s0, s8 *, 4) = temp_v1;
    goto set_done;

set_word:
    {
        M2C_FIELD(temp_s0, s32 *, 4) = (s32) (s16) temp_v1;
    }

set_done:
    func_800667A8(temp_s0, temp_lo);
    M2C_FIELD(temp_s0, u8 *, 7) = (u8) (M2C_FIELD(temp_s0, u8 *, 7) | 2);
    func_8006658C(M2C_FIELD(temp_s1, void **, 0) + 0xB0, temp_s0);
    temp_s0 = M2C_FIELD(M2C_FIELD(temp_s1, void **, 0), void **, 0x8D0);
    M2C_FIELD(M2C_FIELD(temp_s1, void **, 0), void **, 0x8D0) = (void *) (temp_s0 + 0xC);
    M2C_FIELD(temp_s0, s8 *, 3) = 1;
    M2C_FIELD(temp_s0, s32 *, 4) = 0xE1000020;
    func_8006658C(M2C_FIELD(temp_s1, void **, 0) + 0xB0, temp_s0);
    temp_v0 = (u8) M2C_FIELD(arg2, s8 *, 5) - 1;
    M2C_FIELD(arg2, s8 *, 5) = temp_v0;
    if ((temp_v0 << 0x18) == 0) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        D_800814A0[0] = D_800814A0[0] | 0x8000;
    }
}
