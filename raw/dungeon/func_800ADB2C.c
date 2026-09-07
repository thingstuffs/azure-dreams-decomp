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

s32 func_8003DE58();     /* extern */
M2C_UNK func_800B33C8();                      /* extern */
M2C_UNK func_800B8EA8(); /* extern */
extern M2C_UNK D_800814A0;

void func_800B328C(void *arg0, void *arg1) {
    u16 sp28[3];
    u16 sp30[3];
    s16 temp_a1_2;
    s16 temp_a2;
    s32 temp_a3;
    u16 temp_v0;
    u16 temp_v0_2;
    u16 temp_v0_3;
    u16 temp_v0_4;
    void *temp_a0;
    void *temp_a1;

    temp_a1 = M2C_FIELD(M2C_FIELD(arg0, void **, 0), void **, 0xC);
    if (func_8003DE58(M2C_FIELD(temp_a1, s32 *, 8), temp_a1, sp28, 0) != 0) {
        temp_a0 = M2C_FIELD(M2C_FIELD(arg0, void **, 0), void **, 8);
        if (M2C_FIELD(arg0, s16 *, 0x8C) != 0) {
            temp_a1_2 = (s16) M2C_FIELD(arg1, u16 *, 2);
            temp_a2 = (s16) M2C_FIELD(arg1, u16 *, 6);
            temp_a3 = M2C_FIELD(arg1, u16 *, 0xA) << 0x10;
            temp_v0 = M2C_FIELD(temp_a0, u16 *, 2) + sp28[0];
            M2C_FIELD(arg1, u16 *, 2) = temp_v0;
            sp30[0] = temp_v0;
            temp_v0_2 = M2C_FIELD(temp_a0, u16 *, 6) + sp28[1];
            M2C_FIELD(arg1, u16 *, 6) = temp_v0_2;
            sp30[1] = temp_v0_2;
            temp_v0_3 = M2C_FIELD(temp_a0, u16 *, 0xA) + sp28[2];
            M2C_FIELD(arg1, u16 *, 0xA) = temp_v0_3;
            sp30[2] = temp_v0_3;
            func_800B8EA8(M2C_FIELD(arg0, void **, 0), temp_a1_2, temp_a2, temp_a3 >> 0x10, sp30, M2C_FIELD(arg0, s32 *, 4), 2, 0x800, 1);
            func_800B33C8();
            return;
        }
        M2C_FIELD(arg1, u16 *, 2) = (u16) (M2C_FIELD(temp_a0, u16 *, 2) + sp28[0]);
        M2C_FIELD(arg1, u16 *, 6) = (u16) (M2C_FIELD(temp_a0, u16 *, 6) + sp28[1]);
        M2C_FIELD(arg1, u16 *, 0xA) = (u16) (M2C_FIELD(temp_a0, u16 *, 0xA) + sp28[2]);
        M2C_FIELD(arg0, s16 *, 0x8C) = 1;
        func_800B33C8(temp_a0);
        return;
    }
    if ((M2C_FIELD(arg0, s16 *, 0x8C) != 0) || (temp_v0_4 = M2C_FIELD(arg0, u16 *, 0x8E) - 1, M2C_FIELD(arg0, u16 *, 0x8E) = temp_v0_4, ((s16) temp_v0_4 < 0))) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        D_800814A0 |= 0x8000;
    }
}
/* MECHANISM: Sibling u16[3] objects at sp+0x28/sp+0x30 produce the 0x48 frame and s1/s0 hold set.
   Early signed call-argument reads fix scheduling; the restored flag store fixes the two-word CFG cascade.
   A signed halfword decrement test and direct D_800814A0 RMW close the exact tail. */
