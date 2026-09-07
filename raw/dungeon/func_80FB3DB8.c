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

void func_8009A028(void *);
void func_8009A3D0(s32, s32, s32);
void func_800A2FE0(void *);
void func_800A32A4(void *);
void func_800A56E0(s32);
void func_800ACF88(void *);
extern s32 D_800814A0;
extern s32 D_80083460;

void func_801735B8(void *arg0, void *arg1, void *arg2, void *arg3) {
    register void *held_arg2 ASM_REG("$17");
    M2C_UNK *global_ptr;
    s32 state;
    s32 flags;
    s32 global_value;
    s32 call_arg0;
    s32 call_arg1;
    s32 call_arg2;
    u16 countdown;

    held_arg2 = arg2;
    state = M2C_FIELD(arg0, u8 *, 0x9B);
    switch (state) {
    case 0:
        if (M2C_FIELD(&D_80083460, s16 *, 0xA) != 0) {
            return;
        }
        M2C_FIELD(arg0, u8 *, 0x9B) = 1;
        /* fallthrough */
    case 1:
        flags = M2C_FIELD(arg3, s32 *, 0x14);
        if (flags & 0x4000) {
            if (!(flags & 0x20000000)) {
                func_800ACF88(arg3);
            }
        }
        M2C_FIELD(arg0, u16 *, 0x96) = 6;
        M2C_FIELD(arg0, u8 *, 0x9B) =
            (u8)(M2C_FIELD(arg0, u8 *, 0x9B) + 1);
        M2C_FIELD(held_arg2, u16 *, 0x12) = 0xFF80;
        /* fallthrough */
    case 2:
        M2C_FIELD(arg3, s32 *, 0x1C) |= 0x10000000;
        countdown = M2C_FIELD(arg0, u16 *, 0x96) - 1;
        M2C_FIELD(arg0, u16 *, 0x96) = countdown;
        if ((countdown << 16) <= 0) {
            if (M2C_FIELD(held_arg2, u8 *, 0xC) >= 0x10U) {
                M2C_FIELD(held_arg2, s32 *, 0xC) += (s32)0xFFEFEFF0;
            }
            M2C_FIELD(held_arg2, s16 *, 0x10) = 0x20;
            M2C_FIELD(held_arg2, u16 *, 0x14) |= 0xC;
        } else {
            M2C_FIELD(held_arg2, s32 *, 0xC) = 0x00808080;
        }

        if (M2C_FIELD(arg0, s16 *, 0x96) == 0) {
            func_800A56E0(0x805);
        }
        if (!(M2C_FIELD(held_arg2, u16 *, 0x14) & 0x8000)) {
            if (M2C_FIELD(held_arg2, u8 *, 0xC) >= 0x10U) {
                return;
            }
        }

        global_ptr = &D_80083460;
        global_value = M2C_FIELD(global_ptr, s32 *, 0x10);
        if (global_value == (s32)((u8 *)arg3 - 0x20)) {
            M2C_FIELD(global_ptr, s32 *, 0x10) =
                global_value & 0x7FFFFFFF;
        }
        func_800A2FE0(arg3);
        func_800A32A4(arg3);

        call_arg0 = M2C_FIELD(held_arg2, u8 *, 0x24);
        call_arg1 = M2C_FIELD(held_arg2, u8 *, 0x25);
        call_arg2 = 0x3000;
        if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x2000) {
            call_arg2 = 0x300;
        }
        func_8009A3D0(call_arg0, call_arg1, call_arg2);
        func_8009A028(arg3);
        M2C_FIELD(arg3, u16 *, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
        break;
    default:
        return;
    }
    ASM_KEEP(held_arg2);
}

/* MECHANISM: A natural three-case switch preserves the retail dispatch and fallthrough block order.
   A guarded s1 arg2 hold fixes the s0/s1/s2 frame roles; true-space targets remain local joins.
   Direct D_80083460+0xA access schedules the page base, and u16 0xFF80 selects the ori encoding. */
