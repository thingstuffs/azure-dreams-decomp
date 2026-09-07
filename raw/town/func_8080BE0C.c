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

M2C_UNK func_80058588();               /* extern */
s32 func_80071424();                             /* extern */
void func_80526AFC() __attribute__((noreturn));  /* extern */
extern s32 D_80084D5C;
extern s16 D_80530000[];

void func_8080BE0C(void *arg0) {
    s16 *var_v1;
    s16 temp_v1;
    s32 var_a0;
    s32 var_s1;
    u16 temp_v0_2;
    u16 state_value;
    u16 flags_value;
    void *temp_s2;

    var_s1 = 0;
    var_a0 = 7;
    var_v1 = &D_80530000[0x333];
    temp_s2 = M2C_FIELD(arg0, void **, 0xC);
    do {
        var_s1 += *var_v1;
        var_v1 -= 1;
        var_a0 -= 1;
    } while (var_a0 >= 0);
    temp_v1 = M2C_FIELD(arg0, s16 *, 0);
    if (temp_v1 == 0) {
        goto state_0;
    }
    if (temp_v1 == 1) {
        goto state_1;
    }
    func_80526AFC(var_a0);

state_0:
    temp_v0_2 = M2C_FIELD(arg0, u16 *, 2) - 1;
    M2C_FIELD(arg0, u16 *, 2) = temp_v0_2;
    if ((temp_v0_2 << 0x10) > 0) {
        goto done;
    }
    state_value = M2C_FIELD(arg0, u16 *, 0);
    flags_value = M2C_FIELD(arg0, u16 *, 0x1C);
    state_value += 1;
    flags_value &= 0xFFFD;
    M2C_FIELD(arg0, u16 *, 0x1C) = flags_value;
    M2C_FIELD(arg0, u16 *, 0) = state_value;
    func_80526AFC(var_a0);

state_1:
    func_80058588(var_s1, func_80071424(M2C_FIELD(arg0, s32 *, 4)), M2C_FIELD(arg0, s32 *, 4));
    if (M2C_FIELD(temp_s2, u16 *, 0x2A) & 1) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        D_80084D5C |= 0x8000;
    }

done:
    return;
}
/* MECHANISM: The page-base symbol plus &D_80530000[0x333] emits retail's entry lui/addiu in v1.
   A noreturn tail ABI and explicit label order preserve default/state-0/state-1 CFG and jump slots.
   Split state/flags RMW temporaries establish the retail v1/v0 lifetimes and flags/state store order. */
