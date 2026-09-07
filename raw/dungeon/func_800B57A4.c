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

M2C_UNK func_8004491C();           /* extern */
s32 rand();                                /* extern */
M2C_UNK func_800BB02C();                            /* extern */
extern s32 D_800814A0[3];
extern void func_800BABA8(void);

void func_800BAF04(void *arg0) {
    s16 temp_v0;
    s16 temp_v1;
    s16 var_s0;
    u16 temp_v0_2;
    u8 temp_v0_3;

    temp_v1 = M2C_FIELD(arg0, s16 *, 0xA);
    if (temp_v1 != 0) {
        if (temp_v1 != 1) {
            func_800BB02C();
            return;
        }
        goto block_7;
    }
    var_s0 = 0;
    do {
        M2C_FIELD((arg0 + var_s0), s8 *, 0x12) = (s8) (rand() & 0x1F);
        temp_v0 = var_s0 + 1;
        var_s0 = temp_v0;
    } while (temp_v0 < 0x40);
    M2C_FIELD(arg0, u16 *, 0xE) = 0U;
    M2C_FIELD(arg0, s8 *, 0x10) = 0;
    M2C_FIELD(arg0, u8 *, 0x32) = 0U;
    M2C_FIELD(arg0, u8 *, 0x11) = 1U;
    func_8004491C(arg0 - 0x20, func_800BABA8);
    M2C_FIELD(arg0, s16 *, 0xA) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0xA) + 1);
block_7:
    temp_v0_2 = M2C_FIELD(arg0, u16 *, 0xE) + 1;
    M2C_FIELD(arg0, u16 *, 0xE) = temp_v0_2;
    if ((s16) temp_v0_2 >= 0x11) {
        M2C_FIELD(arg0, u16 *, 0xE) = 0U;
    }
    temp_v0_3 = M2C_FIELD(arg0, u8 *, 0x32) + 1;
    M2C_FIELD(arg0, u8 *, 0x32) = temp_v0_3;
    if ((s8) temp_v0_3 >= 0x21) {
        M2C_FIELD(arg0, u8 *, 0x32) = 0x20U;
        M2C_FIELD(arg0, s8 *, 0x10) = 1;
    }
    if (M2C_FIELD(arg0, u8 *, 0x11) == 0) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        D_800814A0[0] |= 0x8000;
    }
}
