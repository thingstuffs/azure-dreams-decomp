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

s32 func_800644B8();                             /* extern */
void func_800F6398(void) __attribute__((noreturn)); /* extern */
extern s32 D_800814A0;
extern u8 D_80173AF8;

void func_800F62BC(void *arg0, s32 arg1, void *arg2) {
    s16 temp_v0_2;
    s32 temp_v0;
    register s32 temp_v1 ASM_REG("$3");
    u8 temp_v1_2;
    void *state = arg0;
    void *actor = arg2;

    if (M2C_FIELD(state, s16 *, 0) == 0) {
        temp_v0 = func_800644B8(M2C_FIELD(state, s16 *, 4) << 7) >> 6;
        temp_v1 = temp_v0 + 0x80;
        temp_v0 = (s32) (temp_v0 << 0x10) >> 0x11;
        temp_v1 += temp_v0;
        ASM_KEEP(temp_v1);
        M2C_FIELD(actor, u8 *, 0xD) = temp_v1;
        M2C_FIELD(actor, u8 *, 0xE) = temp_v1;
        M2C_FIELD(actor, u8 *, 0xC) = temp_v1;
        if (D_80173AF8 != 0) {
            M2C_FIELD(state, s16 *, 2) = 0x20;
            M2C_FIELD(state, u16 *, 0) = (u16) (M2C_FIELD(state, u16 *, 0) + 1);
            func_800F6398();
        }
    } else {
        temp_v1_2 = M2C_FIELD(actor, u8 *, 0xC);
        temp_v1_2 -= (s32) temp_v1_2 / M2C_FIELD(state, s16 *, 2);
        M2C_FIELD(actor, u8 *, 0xC) = temp_v1_2;
        M2C_FIELD(actor, u8 *, 0xD) = temp_v1_2;
        M2C_FIELD(actor, u8 *, 0xE) = temp_v1_2;
        temp_v0_2 = (u16) M2C_FIELD(state, s16 *, 2) - 1;
        M2C_FIELD(state, s16 *, 2) = temp_v0_2;
        if ((temp_v0_2 << 0x10) <= 0) {
            M2C_FIELD(state, u16 *, -2) = (u16) (M2C_FIELD(state, u16 *, -2) | 0x8000);
            D_800814A0 |= 0x8000;
        }
    }
    M2C_FIELD(actor, u16 *, 0x1A) = (u16) (M2C_FIELD(actor, u16 *, 0x1A) + 0x40);
    M2C_FIELD(state, s16 *, 4) = (s16) ((u16) M2C_FIELD(state, s16 *, 4) + 1);
}
/* MECHANISM: Restored the dead middle arg so state/actor naturally hold in s0/s1 with frame 0x20.
   Rebuilt the shared-tail CFG and fade quotient; the noreturn helper exposes the retail tail j.
   A staged v1 color pin, kept before its stores, preserves +0x80 and hoists the global page load. */
