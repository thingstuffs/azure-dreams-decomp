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

M2C_UNK func_800B9204(); /* extern */
extern u8 D_80083160[];
extern u8 D_800D185C;
extern u8 D_800D185D;

void func_800B9260(void) {
    s32 *state = (s32 *) D_80083160;
    s32 flags = state[4];
    register s32 buttons ASM_REG("$4");
    register s32 masked_buttons ASM_REG("$2");

    if (flags < 0) {
        D_800D185C += 0x20;
    }
    if (flags & 0x20000000) {
        D_800D185C++;
    }
    D_800D185C %= 33;
    if (flags & 0x40000000) {
        D_800D185D += 0x42;
    }
    if (flags & 0x10000000) {
        D_800D185D++;
    }
    *(volatile u8 *) &D_800D185D = D_800D185D % 67;
    buttons = *(volatile s32 *) &state[2];
    ASM_KEEP(buttons);
    masked_buttons = buttons & 0x500000;
    ASM_KEEP(masked_buttons);
    if (masked_buttons == 0x500000) {
        func_800B9204(D_800D185D);
    }
}

/* MECHANISM: Hold D_80083160 as a state base and cache flags for the $a3/$a2 lives.
   Type D_800D185C/D as direct bytes and honor func_800B9204's one-argument ABI.
   A volatile store/read seam plus split guarded $a0/$v0 lives fixes the final tail. */
