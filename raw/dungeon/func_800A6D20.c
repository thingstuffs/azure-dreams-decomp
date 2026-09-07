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

M2C_UNK func_800A2B04();              /* extern */
s16 func_800BCB04();                   /* extern */
extern s32 D_80083460[3];

s32 func_800AC480(void *arg0, void *arg1, void *arg2, void *arg3) {
    s32 calc;
    s32 field;
    s32 *global_base;
    s32 step;
    s16 temp_a1;
    s16 temp_v0;
    s16 temp_v0_2;

    temp_a1 = M2C_FIELD(arg0, s16 *, 0x96);
    if (temp_a1 != 0) {
        calc = M2C_FIELD(arg2, u8 *, 0x24) << 6;
        field = M2C_FIELD(arg1, s16 *, 2);
        field -= 0x20;
        calc -= field;
        step = (calc << 0x10) / temp_a1;
        field = M2C_FIELD(arg1, s16 *, 6);
        M2C_FIELD(arg1, s32 *, 0xC) = step;
        calc = M2C_FIELD(arg2, u8 *, 0x25) << 6;
        field -= 0x20;
        calc -= field;
        M2C_FIELD(arg1, s32 *, 0x10) = (calc << 0x10) / (s16) M2C_FIELD(arg0, s16 *, 0x96);
    }
    temp_v0 = (u16) M2C_FIELD(arg0, s16 *, 0x96) - 1;
    M2C_FIELD(arg0, s16 *, 0x96) = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        M2C_FIELD(arg1, s32 *, 0x14) = 0;
        M2C_FIELD(arg1, s32 *, 0x10) = 0;
        M2C_FIELD(arg1, s32 *, 0xC) = 0;
        func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
        temp_v0_2 = func_800BCB04((M2C_FIELD(arg2, u8 *, 0x24) << 6) | 0x20, (M2C_FIELD(arg2, u8 *, 0x25) << 6) | 0x20, (s16) (M2C_FIELD(arg3, u16 *, 0x88) - 0x20));
        if (temp_v0_2 < 0x200) {
            M2C_FIELD(arg0, u16 *, 0x92) = (u16) (M2C_FIELD(arg0, u16 *, 0x92) + (M2C_FIELD(arg3, u16 *, 0x88) - temp_v0_2));
            M2C_FIELD(arg3, u16 *, 0x88) = (u16) temp_v0_2;
        }
        global_base = D_80083460;
        ASM_KEEP(global_base);
        M2C_FIELD(global_base, u16 *, 0xA) = (u16) (M2C_FIELD(global_base, u16 *, 0xA) - 1);
        return 1;
    }
    return 0;
}

/* MECHANISM: Explicit s32 calc/field/step lifetimes preserve each field-0x20
   subtraction and hoist the second lh into the first division's load-delay gap.
   Direct 0/1 returns plus a kept absolute D_80083460 base produce the retail
   v0 delay-slot value and a0-based lhu/sh tail without changing the 0x20 frame. */
