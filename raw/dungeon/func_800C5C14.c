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

M2C_UNK func_800478B8();                      /* extern */
void func_800CB4A8(void);                         /* extern */
typedef struct { s32 v; s32 pad[2]; } S_800814A0;
extern S_800814A0 D_800814A0;

void func_800CB374(void *arg0, void *arg1, void *arg2) {
    s16 temp_v0;
    u8 temp_a0;
    void *temp_v1;

    func_800478B8(arg2);
    if (M2C_FIELD(arg0, s16 *, 0xB4) != 0) {
        M2C_FIELD(arg2, u8 *, 0xC) = (u8) (M2C_FIELD(arg2, u8 *, 0xC) - ((s32) M2C_FIELD(arg2, u8 *, 0xC) / (s16) M2C_FIELD(arg0, s16 *, 0x96)));
        M2C_FIELD(arg2, u8 *, 0xD) = (u8) (M2C_FIELD(arg2, u8 *, 0xD) - ((s32) M2C_FIELD(arg2, u8 *, 0xD) / (s16) M2C_FIELD(arg0, s16 *, 0x96)));
        temp_a0 = M2C_FIELD(arg2, u8 *, 0xE) - ((s32) M2C_FIELD(arg2, u8 *, 0xE) / (s16) M2C_FIELD(arg0, s16 *, 0x96));
        M2C_FIELD(arg2, u8 *, 0xE) = temp_a0;
        M2C_FIELD(arg2, u16 *, 6) = (u16) (M2C_FIELD(arg2, u16 *, 6) - 1);
        temp_v0 = (u16) M2C_FIELD(arg0, s16 *, 0x96) - 1;
        M2C_FIELD(arg0, s16 *, 0x96) = temp_v0;
        if ((temp_v0 << 0x10) > 0) {
            func_800CB4A8();
            return;
        }
        goto block_5;
    }
    M2C_FIELD(arg2, s32 *, 0xC) = M2C_FIELD(M2C_FIELD(arg0, void **, 0xA8), s32 *, 0xCC);
    temp_v1 = M2C_FIELD(M2C_FIELD(arg0, void **, 0xA8), void **, 0xC);
    M2C_FIELD(arg2, u16 *, 0x1C) = (u16) M2C_FIELD(temp_v1, u16 *, 0x1C);
    M2C_FIELD(arg2, u16 *, 0x1E) = (u16) M2C_FIELD(temp_v1, u16 *, 0x1E);
    if (M2C_FIELD(M2C_FIELD(arg0, void **, 0xA8), u16 *, 0x1E) & 0x8000) {
block_5:
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        D_800814A0.v |= 0x8000;
    }
}

/* MECHANISM: The 0x20 frame naturally holds arg0 in s1 and arg2 in s0 across the call.
   A zero-argument tail call and 32-bit fallback copy restore the retail ABI and widths.
   Ordering the +6 halfword decrement after all byte reductions closes the one-word cascade. */
