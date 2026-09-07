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
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
} State;

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

M2C_UNK func_80096A90();                 /* extern */
M2C_UNK func_80096C08();                            /* extern */
M2C_UNK func_80096C24();                            /* extern */
extern s16 D_8006ADD6;
extern s32 D_800FE508[4];
extern State D_800FE520;

void func_80096B50(s32 *arg0) {
    s16 temp_v1;
    State *temp_v0;
    s32 *var_s0;

    var_s0 = arg0;
    D_800FE508[0] = 0x1FFFFFFF;
    D_800FE508[2] = 0x1FFFFFFF;
    D_800FE508[1] = 0;
    D_800FE508[3] = 0;
    if (*var_s0 != 0) {
        do {
            func_80096A90(D_800FE508, *var_s0);
            ASM_SCHED_BARRIER();
            var_s0++;
        } while (*var_s0 != 0);
    }
    temp_v1 = D_8006ADD6;
    if (temp_v1 == 8) {
        D_800FE520.unk0 = 0x03000000;
        D_800FE520.unk4 = 0x04000000;
        {
            register s32 tail_value ASM_REG("$3");

            ASM_SCHED_BARRIER();
            tail_value = 0x02A00000;
            ASM_TAILSLOT_PIN(tail_value);
            func_80096C08();
        }
        return;
    }
    if (temp_v1 == 0xB) {
        D_800FE520.unk0 = 0;
        temp_v0 = &D_800FE520;
        temp_v0->unk4 = 0x04A00000;
        temp_v0->unkC = 0x03B00000;
        temp_v0->unk8 = 0;
        temp_v0->unk10 = 0x80000000;
        func_80096C24();
        return;
    }
    D_800FE520.unk0 = 0x80000000;
}

/* MECHANISM: The 0x20-byte frame naturally saves s0/s1 by holding the input cursor and 0x8010 page across calls.
   Direct array/State fields recover the hi/lo bases and five-word tail record; a direct halfword read rematerializes its page.
   Post-call/pre-tail fences fix scheduling, while a v1-scoped tail pin sinks 0x02A00000 into the shared-tail jump slot. */
