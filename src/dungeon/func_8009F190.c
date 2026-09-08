#include "common.h"
#include "m2c_compat.h"

typedef struct S_800A48F0_0 {
    u8 pad_00[0x2C];
    s8 unk_2C;
    union { u8 s; s8 u; } unk_2D;   /* accessed as both */
} S_800A48F0_0;   /* var_s0 in func_800A48F0 */

typedef struct S_800A48F0_1 {
    u8 pad_00[0x2C];
    s8 unk_2C;
    u8 unk_2D;
} S_800A48F0_1;   /* var_s0_2 in func_800A48F0 */


M2C_UNK func_80042BDC(void *, s32, s32, s32);
extern s32 func_800A48F0__self_recurse(void *, s8, s8) __asm__("func_800A48F0");
s16 func_800A4980(void);
s16 func_800A49E4(void *, s32);
void func_800A4A70(void) __attribute__((noreturn));
void func_800A4A74(void) __attribute__((noreturn));
M2C_UNK func_800A4B88(void *, s8);
M2C_UNK func_80042B68(void *, s32);

s16 func_800A48F0(void *arg0, s32 arg1, s32 arg2) {
    s32 var_a3;
    s32 var_s1;
    s32 temp_a1;
    s32 temp_v0;
    s8 temp_v1;
    register void *held_arg0 ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    register s32 held_arg1 ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    register s32 held_arg2 ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    s32 signed_arg1;
    s32 first_arg1;
    s32 second_arg1;
    void *var_s0;
    void *var_s0_2;
    s32 signed_arg2;

    held_arg0 = arg0;
    temp_a1 = arg1;
    signed_arg2 = arg2;
    held_arg1 = temp_a1;
    held_arg2 = signed_arg2;
    var_a3 = 0x100;
    ASM_KEEP4_NV(held_arg0, held_arg1, held_arg2, var_a3);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    var_s1 = 3;
    signed_arg1 = temp_a1 << 24;
    first_arg1 = signed_arg1 >> 24;
    signed_arg2 <<= 24;
    signed_arg2 >>= 24;
    var_s0 = held_arg0 + 6;
loop_1:
    temp_a1 = ((S_800A48F0_0 *)var_s0)->unk_2C;
    if (temp_a1 == first_arg1) {
        temp_v0 = ((S_800A48F0_0 *)var_s0)->unk_2D.s;
        temp_v0 = (held_arg2 ^ temp_v0) & 0x80;
        if (temp_v0 || (signed_arg2 == 0)) {
            func_80042BDC(held_arg0, temp_a1, signed_arg2, var_a3);
            ((S_800A48F0_0 *)var_s0)->unk_2C = 0;
            ((S_800A48F0_0 *)var_s0)->unk_2D.u = 0;
            return func_800A4980();
        }
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
        ((S_800A48F0_0 *)var_s0)->unk_2D.s = (u8) held_arg2;
        func_800A4B88(held_arg0, (s8)(signed_arg1 >> 24));
        {
            register s32 tail_value ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            tail_value = var_s1 << 16;
            ASM_TAILSLOT_PIN(tail_value);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
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
        temp_v1 = ((S_800A48F0_1 *)var_s0_2)->unk_2C;
        if (temp_v1 == 0) {
            if (second_arg1 == 1) {
                return func_800A49E4(held_arg0, 4);
            }
            if (second_arg1 == 4) {
                void *call_arg0 = held_arg0;
                register s32 one ASM_REG("$5") = 1;   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
                ASM_KEEP_DEP_NV(call_arg0, one);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
                func_80042B68(call_arg0, one);
            }
            ((S_800A48F0_1 *)var_s0_2)->unk_2C = held_arg1;
            ((S_800A48F0_1 *)var_s0_2)->unk_2D = held_arg2;
            func_800A4B88(held_arg0, (s8)(signed_arg1 >> 24));
            {
                register s32 tail_value ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                tail_value = var_s1 << 16;
                ASM_TAILSLOT_PIN(tail_value);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
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
            register s32 final_arg1_shift ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            s32 final_min;
            s32 final_arg1;

            ASM_KEEP_NV(held_arg1);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
            final_arg1_shift = held_arg1 << 24;
            final_min = (s16) var_a3;
            final_arg1 = final_arg1_shift >> 24;

            ASM_KEEP_NV(final_arg1_shift);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            ASM_KEEP_NV(final_min);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            ASM_KEEP_NV(final_arg1);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            if (final_arg1 < final_min) {
                goto final_less;
            }

            {
                void *tail_arg = held_arg0;
                s32 tail_value = -1;
                ASM_TAILSLOT_PIN(tail_value);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
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
