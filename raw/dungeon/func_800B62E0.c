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

M2C_UNK func_8003DB94();    /* extern */
void *func_8003FD64();            /* extern */
M2C_UNK func_8004491C();           /* extern */
M2C_UNK func_800A56E0();                     /* extern */
M2C_UNK func_800BB2E4(); /* extern */
M2C_UNK func_800C77D0(); /* extern */
extern M2C_UNK D_80083498;
extern M2C_UNK D_80083780;
extern M2C_UNK D_800BB55C;
extern M2C_UNK D_800BBA20;
extern M2C_UNK D_800DF3C0;

void *func_800BBA40(s32 arg0, s32 arg1, s16 arg2, M2C_UNK arg3, s32 arg4, s32 arg5, s32 arg6) {
    s32 call_data[2];
    s16 var_a1;
    void *temp_v0;
    void *temp_v1;
    void *temp_v1_2;
    register s32 held_arg0 ASM_REG("$18") = arg0;
    register s32 held_arg1 ASM_REG("$20") = arg1;
    register s16 held_arg2 ASM_REG("$21") = arg2;
    register M2C_UNK held_arg3 ASM_REG("$22") = arg3;
    register void *setup_base ASM_REG("$2");

    call_data[0] = 0x01000340;
    call_data[1] = 0x01000080;
    func_800BB2E4(0, 0, call_data, 1, 0);
    temp_v0 = func_8003FD64(0x12, &D_80083498);
    if (temp_v0 != NULL) {
        register s32 var_a0 ASM_REG("$4");
        register void *var_v1 ASM_REG("$3");

        func_800A56E0(0x704);
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_800BB55C;
        func_8004491C(temp_v0, &D_800BBA20);
        temp_v1 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_v1, s16 *, 2) = (s16) (((s32) (held_arg0 << 0x10) >> 0xA) + 0x20);
        M2C_FIELD(temp_v1, s16 *, 6) = (s16) (((s32) (held_arg1 << 0x10) >> 0xA) + 0x20);
        M2C_FIELD(temp_v1, s16 *, 0xA) = held_arg2;
        temp_v1_2 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_v1_2, M2C_UNK **, 8) = &D_800DF3C0;
        M2C_FIELD(temp_v1_2, s16 *, 0x1E) = 0x1000;
        M2C_FIELD(temp_v1_2, s16 *, 0x1C) = 0x1000;
        M2C_FIELD(temp_v1_2, s32 *, 0xC) = 0x808080;
        M2C_FIELD(temp_v1_2, s16 *, 6) = 8;
        func_8003DB94(temp_v0 + 0x2C, held_arg3, 0);
        ASM_KEEP(held_arg0);
        ASM_KEEP(held_arg1);
        ASM_KEEP(held_arg2);
        ASM_KEEP(held_arg3);
        setup_base = temp_v0 + 0x20;
        ASM_KEEP(setup_base);
        var_v1 = setup_base;
        M2C_FIELD(var_v1, s16 *, 0x2A) = (s16) arg4;
        M2C_FIELD(var_v1, s16 *, 0x28) = (s16) arg4;
        M2C_FIELD(var_v1, s32 *, 0x18) = 0x808080;
        var_a1 = -0x400;
        M2C_FIELD(var_v1, s32 *, 0x5C) = arg5;
        var_a0 = 0;
        M2C_FIELD(var_v1, s32 *, 0x60) = arg6;
        do {
            M2C_FIELD(var_v1, s16 *, 0x3C) = var_a1;
            var_a1 += 0x999;
            var_a0 += 1;
            ASM_KEEP(var_a0);
            var_v1 += 2;
        } while (var_a0 < 5);
        ASM_KEEP(var_v1);
        func_800C77D0(&D_80083498, &D_80083780, 8, 0x300);
    }
    return temp_v0;
}

/* MECHANISM: A two-word stack array preserves both call-data initializers in the 0x40 frame.
   Guarded s2/s4/s5/s6 argument holds reproduce the callee-saved prologue order.
   A pinned v0 split base copies into v1; the pinned a0 counter blocks countdown strength reduction. */
