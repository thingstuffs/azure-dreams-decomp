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

void *func_8003FD64();            /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
extern u8 D_80083160[];
extern M2C_UNK D_80083498;
extern M2C_UNK D_800BB894;

typedef struct Copy24 {
    s32 words[6];
} Copy24;

s32 func_800BB798(void *arg0, s16 arg1, s16 arg2) {
    s32 temp_a0;
    s32 temp_s0;
    s32 temp_s0_2;
    u8 *temp_s1;
    s32 temp_t0;
    s32 temp_v0_math;
    void *temp_v0;
    void *temp_v0_2;
    void *temp_v1;

    temp_s1 = D_80083160;
    temp_a0 = M2C_FIELD(arg0, s32 *, 0x10) + M2C_FIELD(temp_s1, s16 *, 0xC8);
    temp_s0 = M2C_FIELD(arg0, s32 *, 0xC);
    temp_v0_math = func_80064584(temp_a0);
    temp_s0_2 = temp_s0 >> 0xC;
    temp_t0 = temp_s0_2 * temp_v0_math;
    M2C_FIELD(arg0, s32 *, 0xC) = temp_t0;
    temp_a0 = M2C_FIELD(arg0, s32 *, 0x10) + M2C_FIELD(temp_s1, s16 *, 0xC8);
    temp_v0_math = func_800644B8(temp_a0);
    
    
    temp_t0 = temp_s0_2 * temp_v0_math;
    M2C_FIELD(arg0, s32 *, 0x10) = temp_t0;
    temp_v0 = func_8003FD64(0x312, &D_80083498);
    if (temp_v0 != NULL) {
        temp_v1 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_800BB894;
        *(Copy24 *)temp_v1 = *(Copy24 *)arg0;
        temp_v0_2 = temp_v0 + 0x20;
        M2C_FIELD(temp_v0_2, s16 *, 0x48) = arg1;
        M2C_FIELD(temp_v0_2, s16 *, 0x4A) = arg2;
    }
    return 0;
}

/* MECHANISM: A held D_80083160 base in s1 plus destructive s0 and t0 live ranges
   reproduces the 0x28 frame and both multiply/call schedules.  Splitting each
   call argument and using one 24-byte aggregate copy yields the retail a3 hold
   and grouped v0/a0/a1/a2 loads/stores without load-delay nops. */
