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

typedef struct {
    u16 value;
    u8 pad[8];
} Counter;

typedef struct {
    s16 value;
    u8 pad[8];
} Flag;

typedef struct {
    s32 value;
    u8 pad[8];
} Flags;

void func_80024E84(void) __attribute__((noreturn));
void func_80024E8C(void) __attribute__((noreturn));
void func_8002522C();
void func_800262AC();
extern Counter D_80026472;
extern Flag D_80026474;
extern Flags D_800814A0;

void func_80024CD4(void *arg0, void *arg1, void *arg2) {
    s16 state;
    u16 temp_a3;
    u16 temp_v0;
    u16 temp_v0_2;
    u16 temp_v0_3;
    u16 temp_v1_2;
    register void *call_a0 ASM_REG("$4");
    register s32 call_a1 ASM_REG("$5");

    D_80026472.value++;
    state = M2C_FIELD(arg0, s16 *, 0xA);
    if (state == 1) {
        goto state_1;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_0;
        }
        temp_v0 = 0x20;
        M2C_FIELD(arg2, u8 *, 0xC) = temp_v0;
        func_80024E8C();
        return;
    }
    if (state == 2) {
        goto state_2;
    }
    if (state == 3) {
        goto state_3;
    }

    temp_v0 = 0x20;
    M2C_FIELD(arg2, u8 *, 0xC) = temp_v0;
    func_80024E8C();
    return;

state_0:
    temp_v0 = M2C_FIELD(arg2, u16 *, 6) + 0x80;
    M2C_FIELD(arg2, u16 *, 6) = temp_v0;
    if ((s16) temp_v0 < 0x101) {
        temp_v0 = 0x20;
        goto finish;
    }
    M2C_FIELD(arg2, u16 *, 6) = 0x100U;
    if (M2C_FIELD(arg0, s16 *, 0x22) < 0x61) {
        call_a0 = arg1;
        call_a1 = M2C_FIELD(arg0, s16 *, 0x16);
        ASM_USE2(call_a0, call_a1);
        temp_v1_2 = M2C_FIELD(arg0, u16 *, 0x18);
        temp_a3 = M2C_FIELD(arg0, u16 *, 0x1C);
        ASM_USE2(temp_v1_2, temp_a3);
        temp_v1_2 =
            (u16) (temp_v1_2 - ((s32) (temp_v1_2 << 0x10) >> 0x13));
        ASM_SCHED_BARRIER();
        temp_a3 += 0x80;
        ASM_USE(temp_a3);
        M2C_FIELD(arg0, u16 *, 0x1C) = temp_a3;
        M2C_FIELD(arg0, volatile u16 *, 0x18) = temp_v1_2;
        func_8002522C(call_a0, call_a1,
            M2C_FIELD(arg0, s16 *, 0x18), (s16) temp_a3,
            arg0 - 0x20);
    }
    M2C_FIELD(arg0, u16 *, 0xA)++;
    if (M2C_FIELD(arg0, s16 *, 0x22) != 0x6F) {
        temp_v0 = 0x20;
        goto finish;
    }
    D_80026474.value = 1;
    func_80024E84();
    return;

state_1:
    if (D_80026474.value == 0) {
        goto set_20;
    }
    M2C_FIELD(arg2, s16 *, 6) = -0x100;
    M2C_FIELD(arg0, u16 *, 0x1A) = 0x10U;
    M2C_FIELD(arg0, u16 *, 0xA)++;
    func_80024E84();
    return;

state_2:
    temp_v0_2 = M2C_FIELD(arg0, u16 *, 0x1A) - 1;
    M2C_FIELD(arg0, u16 *, 0x1A) = temp_v0_2;
    if ((temp_v0_2 << 0x10) > 0) {
        temp_v0 = 0x20;
        goto finish;
    }
    M2C_FIELD(arg0, u16 *, 0xA)++;

state_3:
    temp_v0_3 = M2C_FIELD(arg2, u16 *, 6) + 0x80;
    M2C_FIELD(arg2, u16 *, 6) = temp_v0_3;
    if ((s16) temp_v0_3 >= 0) {
        M2C_FIELD(arg0, u16 *, -2) |= 0x8000;
        D_800814A0.value |= 0x8000;
    }

set_20:
    ASM_SCHED_BARRIER();
    temp_v0 = 0x20;

finish:
    M2C_FIELD(arg2, u8 *, 0xC) = temp_v0;
    M2C_FIELD(arg2, u8 *, 0xD) = 0xE0;
    M2C_FIELD(arg2, u8 *, 0xE) = 0x40;
    func_800262AC(M2C_FIELD(arg1, s16 *, 2), M2C_FIELD(arg1, s16 *, 6), M2C_FIELD(arg1, s16 *, 0xA));
}

/* MECHANISM: Padded globals force retail hi/lo bases; goto layout preserves the state CFG and noreturn tails.
   A volatile u16 store forces the sh/lh narrowing round trip, while the set_20 fence fixes its delay-slot edge.
   Guarded a0/a1 pins plus zero-byte liveness fences reproduce the final call-argument schedule. */
