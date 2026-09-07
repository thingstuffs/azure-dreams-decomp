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

void *func_7003CF18();                       /* extern */
s32 func_700750E0();                                /* extern */
M2C_UNK func_7010CD00(); /* extern */
extern s32 D_80086AD8;
extern u8 D_800E0F20[0x100];
extern u16 D_80094422;
extern M2C_UNK D_8010C994;

void func_7FFEA9D4(void *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    register M2C_UNK saved_arg1 ASM_REG("$22") = arg1;
    register M2C_UNK saved_arg2 ASM_REG("$23") = arg2;
    register s32 delta ASM_REG("$4");
    s32 var_s4;
    s32 rand_value;
    s32 current;
    s32 first_current;
    s32 second_current;
    u16 temp_v0;
    u16 temp_v0_3;
    u16 counter_value;
    u16 *counter;
    void *temp_s0;
    void *temp_s1;
    void *temp_v0_2;

    temp_v0 = M2C_FIELD(arg0, u16 *, 0x16) + 1;
    M2C_FIELD(arg0, u16 *, 0x16) = temp_v0;
    if ((s16) temp_v0 < 0x28) {
        var_s4 = 0;
        do {
            temp_v0_2 = func_7003CF18(0x212);
            var_s4 += 1;
            if (temp_v0_2 != NULL) {
                ASM_KEEP_NV(saved_arg1);
                ASM_KEEP_NV(saved_arg2);
                func_7010CD00(temp_v0_2, arg0, saved_arg1, saved_arg2);
                temp_s0 = M2C_FIELD(temp_v0_2, void **, 8);
                M2C_FIELD(temp_v0_2, s16 *, 0x3E) = 8;
                M2C_FIELD(temp_v0_2, s16 *, 0x40) = 8;
                M2C_FIELD(temp_v0_2, M2C_UNK **, 0x10) = &D_8010C994;
                rand_value = func_700750E0();
                first_current = M2C_FIELD(temp_s0, u16 *, 2);
                first_current -= 0x1F;
                first_current += rand_value & 0x3F;
                M2C_FIELD(temp_s0, u16 *, 2) = (u16) first_current;
                rand_value = func_700750E0();
                second_current = M2C_FIELD(temp_s0, u16 *, 6);
                second_current -= 0x1F;
                second_current += rand_value & 0x3F;
                M2C_FIELD(temp_s0, u16 *, 6) = (u16) second_current;
                temp_s1 = M2C_FIELD(arg0, void **, 0);
                M2C_FIELD(temp_v0_2, u16 *, 0x60) = (u16) M2C_FIELD(temp_s0, u16 *, 0xA);
                rand_value = func_700750E0();
                delta = D_800E0F20[M2C_FIELD(temp_s1, u8 *, 0x13)];
                current = M2C_FIELD(temp_s0, u16 *, 0xA);
                delta += 0x20;
                ASM_KEEP_NV(delta);
                delta -= rand_value & 0xF;
                current -= delta;
                M2C_FIELD(temp_s0, u16 *, 0xA) = (u16) current;
                M2C_FIELD(M2C_FIELD(temp_v0_2, void **, 0xC), s32 *, 0xC) = 0;
            }
        } while (var_s4 < 2);
    }
    temp_v0_3 = M2C_FIELD(arg0, u16 *, 0x1E) - 1;
    M2C_FIELD(arg0, u16 *, 0x1E) = temp_v0_3;
    if ((temp_v0_3 << 0x10) <= 0) {
        temp_v0 = M2C_FIELD(arg0, u16 *, -2);
        counter = &D_80094422;
        temp_v0 |= 0x8000;
        M2C_FIELD(arg0, u16 *, -2) = temp_v0;
        counter_value = *counter - 1;
        D_80086AD8 |= 0x8000;
        *counter = counter_value;
    }
}

/* MECHANISM: Dedicated short-lived RNG locals preserve retail's immediate arithmetic order.
   Guarded argument roles and a late $a0 delta keep reproduce the saved and scratch coloring.
   A held counter pointer/value orders the final global RMW and fills both load-delay slots. */
