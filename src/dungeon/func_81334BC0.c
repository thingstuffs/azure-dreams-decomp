#include "common.h"
#include "records/Rec_func_800A9E70_arg0.h"

typedef struct S_8016BBC0_0 {
    u8 pad_00[0x46];
    u16 unk_46;
    u8 pad_48[0x29];
    u8 unk_71;
    u8 pad_72[0x3C];
    u8 unk_AE;
} S_8016BBC0_0;   /* base in func_8016BBC0 */




extern s32 func_800A2BDC(void *);
extern void func_800A9A0C(void *);
extern s16 func_800ADDA0(s32, s32, void *, s32, s32, void *);
extern void func_8016B230(void *, s32, s32, void *);
extern u16 D_80083462;

s32 func_8016BBC0(Rec_func_800A9E70_arg0 *arg0, s32 arg1, s32 arg2, s32 arg3)
{
    void *base = arg0;
    s16 var_v1;
    s32 var_v0;
    u8 temp_v0;
    register void *case2_a0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */

    temp_v0 = ((S_8016BBC0_0 *)base)->unk_AE;
    var_v1 = 0;
    if (temp_v0 == 0) {
        var_v1 = func_800ADDA0(arg1, arg2, base, 3, 6,
                              (u8 *)base + 0x9C);
        if ((s16)var_v1 < 0) {
            return 0;
        }
        if ((arg3 << 16) != 0) {
            register void *call_a0 ASM_REG("$4") = base;   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            register s32 call_a1 ASM_REG("$5") = arg1;   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            s32 call_a2 = arg2;
            void *call_a3 = base;
            ASM_KEEP(call_a2);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            func_8016B230(call_a0, call_a1, call_a2, call_a3);
            return 0;
        }
        goto block_8;
    }
    ((S_8016BBC0_0 *)base)->unk_AE = temp_v0 - 1;

block_8:
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    if (var_v1 == 1) {
        goto case_1;
    }
    if (var_v1 < 2) {
        var_v0 = 0xE;
        if (var_v1 == 0) {
            goto case_0;
        }
        goto block_tail;
    }
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    case2_a0 = arg0;
    if (var_v1 == 2) {
        goto case_2;
    }
    goto block_tail;

case_0: {
        arg0->unk_9A.as_s8 = var_v0;
        func_800A9A0C(base);
        return 0;
    }

case_2: {
        register s32 call_a1 ASM_REG("$5") = arg1;   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        register s32 call_a2 ASM_REG("$6") = arg2;   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        void *call_a3 = base;
        ASM_KEEP(call_a3);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        func_8016B230(case2_a0, call_a1, call_a2, call_a3);
        return 0;
    }

case_1:
    ((S_8016BBC0_0 *)base)->unk_71 &= 0x7F;
    if ((func_800A2BDC(base) << 16) != 0) {
        goto block_clear;
    }
    goto block_tail;

block_tail:
    ((S_8016BBC0_0 *)base)->unk_71 &= 0x7F;
    var_v0 = 1;
    if (!(D_80083462 & 8)) {
        return var_v0;
    }

block_clear:
    var_v0 = 0;
    ((S_8016BBC0_0 *)base)->unk_46 &= 0x7FFF;
    return var_v0;
}

/* MECHANISM: Natural lexical CFG yields the 0x30 frame, ordered s1-s4 arguments, and s0 held base.
   Noreturn tails plus guarded v0/a3 tail-slot pins reproduce retail's j delay slots.
   Held case-2 a0 and ordered a1/a2/a3 pins preserve the jal nop and exact block layout. */
