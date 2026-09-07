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

s32 rand(void);                      /* extern */

void func_800BD688(void *arg0_in) {
    register void *arg0 ASM_REG("$18") = arg0_in;
    s32 temp_v1;
    s32 temp_v0_2;
    s32 temp_v1_4;
    s32 upper;
    s32 decrement;
    s32 var_s1;
    register s32 var_v0 ASM_REG("$2");
    s32 var_v0_2;
    u16 temp_v0;
    register s32 *page ASM_REG("$3");
    void **var_s0;
    void *temp_a0;
    void *temp_a0_2;
    void *temp_a1;
    void *temp_v1_2;
    void *temp_v1_3;
    void *var_a0;

    ASM_KEEP(arg0);
    temp_v1 = M2C_FIELD(arg0, s16 *, 0x20);
    temp_v0 = (M2C_FIELD(arg0, u16 *, 0x22) + 1) & 7;
    M2C_FIELD(arg0, u16 *, 0x22) = temp_v0;
    if (temp_v1 == 0) {
        goto state_zero;
    }
    if (temp_v1 == 1) {
        goto state_one;
    }
    goto done;

state_zero:
    var_a0 = (void *)0xFEC00000;
    if (temp_v0 == 0) {
        {
            void *left_ptr;
            void *right_ptr;

            left_ptr = M2C_FIELD(arg0, void **, 0);
            right_ptr = M2C_FIELD(arg0, void **, 4);
            var_v0 = M2C_FIELD(left_ptr, s32 *, 0);
            var_v0 -= M2C_FIELD(right_ptr, s32 *, 0);
        }
        if (var_v0 < 0) {
            var_v0 = 0 - var_v0;
        }
        ASM_KEEP(var_v0);
        {
            register u32 range ASM_REG("$3");

            range = var_v0 + 0xFFE00000;
            ASM_KEEP(range);
            if (range > 0x200000U) {
                var_s1 = 1;
                upper = 0x7FFFF;
                decrement = 0xFFF80000;
                var_s0 = arg0 + 4;
                do {
                    temp_v0_2 = rand();
                    var_a0 = *var_s0;
                    var_v0_2 = (temp_v0_2 & 0x1FF) << 8;
                    if (M2C_FIELD(var_a0, s32 *, 0xC) > upper) {
                        var_v0_2 = 0 - var_v0_2;
                    }
                    M2C_FIELD(var_a0, s32 *, 0xC) = var_v0_2;
                    temp_v1_2 = *var_s0;
                    var_s0 = (void **)((s8 *)((void **)((s8 *)var_s0 - 4)));
                    var_s1 -= 1;
                    M2C_FIELD(temp_v1_2, s32 *, 0xC) = (s32) (M2C_FIELD(temp_v1_2, s32 *, 0xC) + decrement);
                } while (var_s1 >= 0);
            }
        }
        var_s1 = 1;
        var_s0 = arg0 + 4;
        do {
            temp_v0_2 = rand();
            var_s1 -= 1;
            temp_v1_3 = *var_s0;
            var_s0 = (void **)((s8 *)((void **)((s8 *)var_s0 - 4)));
            M2C_FIELD(temp_v1_3, s32 *, 0x10) = (s32) (((temp_v0_2 & 0x1FF) - 0x100) << 9);
        } while (var_s1 >= 0);
        M2C_FIELD(M2C_FIELD(arg0, void **, 0), s32 *, 0x14) = (s32) (((rand() & 0x1FF) - 0x100) << 8);
        M2C_FIELD(M2C_FIELD(arg0, void **, 4), s32 *, 0x14) = (s32) ((rand() & 0x1FF) << 7);
        temp_a0 = M2C_FIELD(arg0, void **, 4);
        if (M2C_FIELD(M2C_FIELD(arg0, void **, 0), s32 *, 8) < M2C_FIELD(temp_a0, s32 *, 8)) {
            M2C_FIELD(temp_a0, s32 *, 0x14) = (s32) (0 - M2C_FIELD(temp_a0, s32 *, 0x14));
        }
    }
    temp_a1 = M2C_FIELD(arg0, void **, 0);
    temp_v1_4 = M2C_FIELD(arg0, s32 *, 8) + 0xFEC00000;
    if (M2C_FIELD(temp_a1, s32 *, 0) < temp_v1_4) {
        temp_a0_2 = M2C_FIELD(arg0, void **, 4);
        if (M2C_FIELD(temp_a0_2, s32 *, 0) < temp_v1_4) {
            M2C_FIELD(temp_a0_2, s32 *, 0xC) = 0;
            M2C_FIELD(temp_a1, s32 *, 0xC) = 0;
            M2C_FIELD(arg0, u16 *, 0x20) += 1;
        }
    }
    goto done;

state_one:
    page = (s32 *)0x80080000;
    ASM_KEEP(page);
    M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
    page[0x14A0 / 4] |= 0x8000;

done:
    return;
}

/* MECHANISM: True-space CFG labels place the state-one tail after the main path and preserve the 0x28 frame.
   Reused s1/s0 loop locals plus the zero-argument RNG shape recover the retail call slots and saved-register roles.
   Guarded v0/v1 runtime values and the held 0x80080000 page base close coloring and +0x14A0 addressing. */
