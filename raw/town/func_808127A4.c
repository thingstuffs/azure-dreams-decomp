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

M2C_UNK func_80058588();           /* extern */
void func_8052D4A0(void) __attribute__((noreturn)); /* extern */
extern s32 D_80084D5C;

void func_808127A4(void *arg0) {
    s16 temp_v1;
    u32 temp_a0;
    u16 temp_step;
    u16 temp_v0;
    u32 temp_condition;
    void *temp_s1;

    temp_v1 = M2C_FIELD(arg0, s16 *, 0);
    temp_s1 = M2C_FIELD(arg0, void **, 0xC);
    if (temp_v1 == 0) {
        goto state_0;
    }
    if (temp_v1 == 1) {
        goto state_1;
    }
    func_8052D4A0();
    return;

state_0:
    func_80058588(*M2C_FIELD(arg0, u16 **, 8) * 0x3E8, 5, M2C_FIELD(arg0, s32 *, 4) + 4);
    if (M2C_FIELD(temp_s1, s16 *, 0x5C) != 3) {
        return;
    }
    if (M2C_FIELD(arg0, s16 *, 0x16) >= 0x78) {
        M2C_FIELD(arg0, s16 *, 2) = 8;
    } else {
        M2C_FIELD(arg0, s16 *, 2) = -8;
    }
    ASM_MEM_BARRIER();
    M2C_FIELD(arg0, u16 *, 0)++;
    func_8052D4A0();
    return;

state_1:
    temp_a0 = M2C_FIELD(arg0, u16 *, 0x16);
    temp_step = M2C_FIELD(arg0, u16 *, 2);
    temp_v0 = M2C_FIELD(arg0, volatile u16 *, 2);
    temp_a0 += temp_step;
    temp_v0 = temp_a0 + ((s32) (temp_v0 << 0x10) >> 0x12);
    temp_condition = (temp_v0 + 8) & 0xFFFF;
    ASM_SCHED_BARRIER();
    M2C_FIELD(arg0, volatile u16 *, 0x16) = temp_a0;
    M2C_FIELD(arg0, u16 *, 0x16) = temp_v0;
    if (temp_condition >= 0xF9U) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        *(s32 *) 0x80084D5C = D_80084D5C | 0x8000;
    }
}

/* MECHANISM: Retail-order state labels preserve the 0x20 s0/s1 frame and CFG.
   Noreturn tails plus named fences hold both RMW and delay-slot store shapes.
   Split predicate/read lifetimes and signed s16 arm stores recover a0/v1/v0 roles.
   Symbolic load plus literal store forces independent global load/store bases. */
