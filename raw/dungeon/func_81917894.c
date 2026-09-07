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

M2C_UNK func_80024E80();              /* extern */
void func_80025150(void) __attribute__((noreturn)); /* extern */
void func_800251FC(void) __attribute__((noreturn)); /* extern */
void func_80025254(void) __attribute__((noreturn)); /* extern */
M2C_UNK func_800478B8();                      /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
extern s32 D_800814A0;

void func_80025094(void *arg0, void *arg1, void *arg2) {
    s32 temp_v0_2;
    s16 temp_v1_2;
    u8 temp_v0;
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, void **, 0);
    M2C_FIELD(temp_v1, u16 *, 0x14) = (u16) (M2C_FIELD(temp_v1, u16 *, 0x14) + 1);
    func_800478B8(arg2);
    M2C_FIELD(arg0, u16 *, 6) = (u16) (M2C_FIELD(arg0, u16 *, 6) + 1);
    M2C_FIELD(arg2, u16 *, 0x1A) = (u16) (M2C_FIELD(arg2, u16 *, 0x1A) + 0x200);
    temp_v1_2 = M2C_FIELD(arg0, s16 *, 4);

    if (temp_v1_2 == 1) {
        goto state_1;
    }
    if (temp_v1_2 < 2) {
        if (temp_v1_2 == 0) {
            goto state_0;
        }
        ASM_SCHED_BARRIER();
        func_800251FC();
    }
    if (temp_v1_2 == 2) {
        goto state_2;
    }
    func_800251FC();

state_0:
    if (M2C_FIELD(arg0, u16 *, 6) & 1) {
        u16 tail_value;

        tail_value = M2C_FIELD(arg0, u16 *, 0xA) + 2;
        ASM_TAILSLOT_PIN(tail_value);
        func_80025150();
    }
    M2C_FIELD(arg0, u16 *, 0xA) =
        (u16) (M2C_FIELD(arg0, u16 *, 0xA) + 1);
    temp_v0 = M2C_FIELD(arg2, u8 *, 0xE) + 3;
    M2C_FIELD(arg2, u8 *, 0xE) = temp_v0;
    M2C_FIELD(arg2, u8 *, 0xD) = temp_v0;
    M2C_FIELD(arg2, u8 *, 0xC) = temp_v0;
    temp_v0_2 = M2C_FIELD(arg0, s16 *, 6) << 5;
    M2C_FIELD(arg2, s16 *, 0x1E) = temp_v0_2;
    M2C_FIELD(arg2, s16 *, 0x1C) = temp_v0_2;
    M2C_FIELD(arg1, u16 *, 0xA) =
        (u16) (M2C_FIELD(arg1, u16 *, 0xA) - 2);

state_1:
    if ((s16) M2C_FIELD(arg0, u16 *, 6) >= 0x20) {
        M2C_FIELD(arg0, u16 *, 6) = 0U;
        M2C_FIELD(arg0, u16 *, 4) =
            (u16) (M2C_FIELD(arg0, u16 *, 4) + 1);
        func_800251FC();
    }
    goto common;

state_2:
    if ((s16) M2C_FIELD(arg0, u16 *, 6) >=
            M2C_FIELD(arg0, s16 *, 8)) {
        func_80024E80(arg0, arg1);
        M2C_FIELD(arg0, u16 *, -2) =
            (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        D_800814A0 |= 0x8000;
        func_80025254();
    }

common:
    M2C_FIELD(arg1, s16 *, 2) = (s16) (M2C_FIELD(arg1, u16 *, 0xE) + ((s32) ((func_80064584(M2C_FIELD(arg0, s16 *, 0xC)) >> 4) * (s16) M2C_FIELD(arg0, u16 *, 0xA)) >> 8));
    M2C_FIELD(arg1, s16 *, 6) = (s16) (M2C_FIELD(arg1, u16 *, 0x12) + ((s32) ((func_800644B8(M2C_FIELD(arg0, s16 *, 0xC)) >> 4) * (s16) M2C_FIELD(arg0, u16 *, 0xA)) >> 8));
}

/* MECHANISM: Explicit invalid-state predecessors plus a one-sided scheduling barrier
   prevent GCC from merging retail's two dispatcher tails. A guarded $v0 tail-slot pin
   preserves the hidden +2 continuation value; an s32 scale temp forces the signed lh. */
