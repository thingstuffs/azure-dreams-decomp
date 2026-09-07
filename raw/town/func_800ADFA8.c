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

s32 func_800AAE98();                          /* extern */
M2C_UNK func_800AAFE0();          /* extern */
M2C_UNK func_800AB014();             /* extern */
s32 func_800AB030();                          /* extern */
extern M2C_UNK D_800AB5C0;

typedef struct {
    s16 unk0;
    u16 value;
} LocalEntry;

void func_800AB708(void *arg0, void *arg1) {
    LocalEntry sp10[6];
    register void *call_arg ASM_REG("$4");
    register s32 call_result ASM_REG("$2");
    s32 temp_s0;
    u16 stack_value;

    func_800AAFE0(sp10, 4);
    call_result = func_800AAE98(arg1);
    ASM_KEEP(call_result);
    call_arg = arg0;
    ASM_KEEP(call_arg);
    temp_s0 = call_result;
    call_result = func_800AB030(call_arg);
    stack_value = sp10[2].value;
    temp_s0 += call_result;
    sp10[2].value = stack_value - temp_s0;
    M2C_FIELD(arg1, s16 *, 2) = (s16) ((s32) (M2C_FIELD(arg1, s16 *, 2) + (s16) sp10[0].value) / 2);
    M2C_FIELD(arg1, s16 *, 6) = (s16) ((s32) (M2C_FIELD(arg1, s16 *, 6) + (s16) sp10[1].value) / 2);
    M2C_FIELD(arg1, s16 *, 0xA) = (s16) ((s32) (M2C_FIELD(arg1, s16 *, 0xA) + (s16) sp10[2].value) / 2);
    func_800AB014(arg0, 4);
    if (M2C_FIELD(arg0, s16 *, 0x90) >= 0x64) {
        M2C_FIELD(arg0, M2C_UNK **, 0x50) = &D_800AB5C0;
        M2C_FIELD(arg0, s16 *, 0x72) = 0;
        M2C_FIELD(arg0, s16 *, 0x6C) = 0xA;
    }
}

/* MECHANISM: A six-entry 4-byte sibling array creates the 24-byte stack object and exact 0x38 frame.
   Guarded $v0/$a0 ABI pins place the first return save in the second call's delay slot.
   A named u16 RMW value yields lhu-v1/subu/sh, and 2.7.2-cdk-G0 fills the final branch with the lui. */
