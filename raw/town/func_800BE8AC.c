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

typedef struct {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fc;
    s32 f10;
    s32 f14;
} State1;

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

M2C_UNK func_800478B8();                      /* extern */
s32 func_800BC1C0();               /* extern */
extern s32 func_800BC1C0_state0(void) __asm__("func_800BC1C0");
extern s32 D_800814A0[3];

s32 func_800BC00C(void *arg0, void *arg1, void *arg2) {
    s16 temp_v1;
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_v0_2;
    s32 temp_v1_2;
    s32 var_v0;
    s32 state0_v0;
    u16 temp_v0;

    M2C_FIELD(arg0, u16 *, 0x48) = (u16) (M2C_FIELD(arg0, u16 *, 0x48) - 1);
    func_800478B8(arg2);
    temp_v1 = M2C_FIELD(arg0, s16 *, 0x4C);
    if (temp_v1 == 1) {
        goto state_1;
    }
    if (temp_v1 >= 2) {
        goto check_ff;
    }
    if (temp_v1 == 0) {
        goto state_0;
    }
    return func_800BC1C0();

check_ff:
    ASM_SCHED_BARRIER();
    if (temp_v1 == 0xFF) {
        goto state_ff;
    }
    return func_800BC1C0();

state_0:
    temp_v0 = M2C_FIELD(arg2, u16 *, 0x1E) + 0x80;
    M2C_FIELD(arg2, u16 *, 0x1E) = temp_v0;
    M2C_FIELD(arg2, u16 *, 0x1C) = temp_v0;
    M2C_FIELD(arg2, s32 *, 0xC) = (s32) (M2C_FIELD(arg2, s32 *, 0xC) + 0x80808);
    M2C_FIELD(arg1, s16 *, 2) = (s16) ((u16) M2C_FIELD(arg1, s16 *, 2) + ((s32) (M2C_FIELD(arg0, s16 *, 0xC) - M2C_FIELD(arg1, s16 *, 2)) >> 2));
    M2C_FIELD(arg1, s16 *, 6) = (s16) ((u16) M2C_FIELD(arg1, s16 *, 6) + ((s32) (M2C_FIELD(arg0, s16 *, 0xE) - M2C_FIELD(arg1, s16 *, 6)) >> 2));
    M2C_FIELD(arg1, s16 *, 0xA) = (s16) ((u16) M2C_FIELD(arg1, s16 *, 0xA) + ((s32) (M2C_FIELD(arg0, s16 *, 0x10) - M2C_FIELD(arg1, s16 *, 0xA)) >> 2));
    state0_v0 = 0xFF;
    if ((s16) M2C_FIELD(arg0, u16 *, 0x48) > 0) {
        goto state_0_done;
    }
    M2C_FIELD(arg0, s16 *, 0x4C) = state0_v0;
    return func_800BC1C0_state0();
state_0_done:
    return state0_v0;

state_1:
    {
        State1 *p = (State1 *)arg1;
        p->f0 = p->f0 + p->fc;
        p->f4 = p->f4 + p->f10;
        p->f8 = p->f8 + p->f14;
        p->fc = p->fc - (p->fc >> 3);
        p->f10 = p->f10 - (p->f10 >> 3);
        p->f14 = p->f14 - (p->f14 >> 3);
    }
    M2C_FIELD(arg2, s32 *, 0xC) = (s32) (M2C_FIELD(arg2, s32 *, 0xC) + 0xFFF7F7F8);
    temp_v0_2 = 0xFF;
    if ((u8) M2C_FIELD(arg2, s32 *, 0xC) == 0) {
        M2C_FIELD(arg0, s16 *, 0x4C) = temp_v0_2;
        return func_800BC1C0();
    }
    return temp_v0_2;

state_ff:
    M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
    var_v0 = D_800814A0[0] | 0x8000;
    D_800814A0[0] = var_v0;
    return var_v0;
}
