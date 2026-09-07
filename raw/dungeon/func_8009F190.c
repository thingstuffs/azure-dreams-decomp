#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;
typedef s8  M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_80042BDC(void *, s32, s32, s32);
extern s32 func_800A48F0__self_recurse(void *, s8, s8) __asm__("func_800A48F0");
s16 func_800A4980(void);
s16 func_800A49E4(void *, s32);
void func_800A4A70(void) __attribute__((noreturn));
void func_800A4A74(void) __attribute__((noreturn));
M2C_UNK func_800A4B88(void *, s8);
M2C_UNK func_80042B68(void *, s32);

s16 func_800A48F0(void *arg0, s32 arg1, s32 arg2) {
    register s32 var_a3 ASM_REG("$7");
    register s32 var_s1 ASM_REG("$17");
    register s32 temp_a1 ASM_REG("$5");
    register s32 temp_v0 ASM_REG("$2");
    s8 temp_v1;
    register void *held_arg0 ASM_REG("$19");
    register s32 held_arg1 ASM_REG("$21");
    register s32 held_arg2 ASM_REG("$18");
    register s32 signed_arg1 ASM_REG("$20");
    register s32 first_arg1 ASM_REG("$2");
    register s32 second_arg1 ASM_REG("$4");
    void *var_s0;
    void *var_s0_2;
    register s32 signed_arg2 ASM_REG("$6");

    held_arg0 = arg0;
    temp_a1 = arg1;
    signed_arg2 = arg2;
    held_arg1 = temp_a1;
    held_arg2 = signed_arg2;
    var_a3 = 0x100;
    ASM_KEEP4_NV(held_arg0, held_arg1, held_arg2, var_a3);
    var_s1 = 3;
    ASM_KEEP_NV(var_s1);
    signed_arg1 = temp_a1 << 24;
    first_arg1 = signed_arg1 >> 24;
    signed_arg2 <<= 24;
    signed_arg2 >>= 24;
    ASM_KEEP_NV(signed_arg2);
    ASM_KEEP_NV(var_a3);
    var_s0 = held_arg0 + 6;
loop_1:
    temp_a1 = M2C_FIELD(var_s0, s8 *, 0x2C);
    if (temp_a1 == first_arg1) {
        ASM_KEEP_NV(temp_a1);
        temp_v0 = M2C_FIELD(var_s0, u8 *, 0x2D);
        ASM_KEEP_NV(temp_v0);
        temp_v0 = (held_arg2 ^ temp_v0) & 0x80;
        if (temp_v0 || (signed_arg2 == 0)) {
            func_80042BDC(held_arg0, temp_a1, signed_arg2, var_a3);
            M2C_FIELD(var_s0, s8 *, 0x2C) = 0;
            M2C_FIELD(var_s0, s8 *, 0x2D) = 0;
            return func_800A4980();
        }
        ASM_SCHED_BARRIER();
        M2C_FIELD(var_s0, u8 *, 0x2D) = (u8) held_arg2;
        func_800A4B88(held_arg0, (s8)(signed_arg1 >> 24));
        {
            register s32 tail_value ASM_REG("$2");
            tail_value = var_s1 << 16;
            ASM_TAILSLOT_PIN(tail_value);
            func_800A4A70();
            return tail_value;
        }
    }
    var_s1 -= 1;
    var_s0 -= 2;
    if (var_s1 < 0) {
        var_s1 = 3;
        signed_arg1 = held_arg1 << 24;
        second_arg1 = signed_arg1 >> 24;
        var_s0_2 = held_arg0 + 6;
loop_10:
        temp_v1 = M2C_FIELD(var_s0_2, s8 *, 0x2C);
        if (temp_v1 == 0) {
            if (second_arg1 == 1) {
                return func_800A49E4(held_arg0, 4);
            }
            if (second_arg1 == 4) {
                register void *call_arg0 ASM_REG("$4") = held_arg0;
                register s32 one ASM_REG("$5") = 1;
                ASM_KEEP_DEP_NV(call_arg0, one);
                func_80042B68(call_arg0, one);
            }
            M2C_FIELD(var_s0_2, s8 *, 0x2C) = held_arg1;
            M2C_FIELD(var_s0_2, u8 *, 0x2D) = held_arg2;
            func_800A4B88(held_arg0, (s8)(signed_arg1 >> 24));
            {
                register s32 tail_value ASM_REG("$2");
                tail_value = var_s1 << 16;
                ASM_TAILSLOT_PIN(tail_value);
                func_800A4A70();
                return tail_value;
            }
        }
        if (temp_v1 < (s16) var_a3) {
            var_a3 = temp_v1;
        }
        var_s1 -= 1;
        var_s0_2 -= 2;
        if (var_s1 < 0) {
            register s32 final_arg1_shift ASM_REG("$16");
            register s32 final_min ASM_REG("$3");
            register s32 final_arg1 ASM_REG("$2");

            ASM_KEEP_NV(held_arg1);
            final_arg1_shift = held_arg1 << 24;
            final_min = (s16) var_a3;
            final_arg1 = final_arg1_shift >> 24;

            ASM_KEEP_NV(final_arg1_shift);
            ASM_KEEP_NV(final_min);
            ASM_KEEP_NV(final_arg1);
            if (final_arg1 < final_min) {
                goto final_less;
            }

            {
                register void *tail_arg ASM_REG("$4") = held_arg0;
                register s32 tail_value ASM_REG("$2") = -1;
                ASM_KEEP_NV(tail_arg);
                ASM_TAILSLOT_PIN(tail_value);
                func_800A4A74();
                return tail_value;
            }

final_less:
            func_80042B68(held_arg0, (s8) var_a3);
            return func_800A48F0__self_recurse(held_arg0, (s8)(final_arg1_shift >> 24), (s8)held_arg2);
        }
        goto loop_10;
    }
    goto loop_1;
}
