#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s32 func_800A2BDC(void *);
extern void func_800A9A0C(void *);
extern s16 func_800ADDA0(s32, s32, void *, s32, s32, void *);
extern void func_8016BF74(void *, s32, s32, void *);
extern void func_8016CA80(void) __attribute__((noreturn));
extern void func_8016CAB0(void) __attribute__((noreturn));
extern void func_8016CAE8(void) __attribute__((noreturn));
extern u16 D_80083462;

s32 func_8016C98C(void *arg0, s32 arg1, s32 arg2, s32 arg3)
{
    void *base = arg0;
    s16 var_v1;
    s32 var_v0;
    register void *case2_a0 ASM_REG("$4");

    if (FIELD(base, u16, 0xAE) != 0) {
        var_v1 = func_800ADDA0(arg1, arg2, base, 3, 6,
                              (u8 *)base + 0x9C);
        if ((s16)var_v1 < 0) {
            register s32 tail_result ASM_REG("$2") = 0;
            ASM_TAILSLOT_PIN(tail_result);
            func_8016CAE8();
            return tail_result;
        }
        if ((arg3 << 16) != 0) {
            register void *call_a0 ASM_REG("$4") = base;
            register s32 call_a1 ASM_REG("$5") = arg1;
            register s32 call_a2 ASM_REG("$6") = arg2;
            register void *call_a3 ASM_REG("$7") = base;
            ASM_KEEP(call_a0);
            ASM_KEEP(call_a1);
            ASM_KEEP(call_a2);
            ASM_TAILSLOT_PIN(call_a3);
            func_8016CA80();
        }
        goto block_8;
    }
    var_v1 = 0;

block_8:
    ASM_SCHED_BARRIER();
    if (var_v1 == 1) {
        goto case_1;
    }
    if (var_v1 < 2) {
        var_v0 = 0xE;
        if (var_v1 == 0) {
            goto case_0;
        }
        func_8016CAB0();
        ASM_SCHED_BARRIER();
    }
    ASM_SCHED_BARRIER();
    case2_a0 = arg0;
    if (var_v1 == 2) {
        goto case_2;
    }
    func_8016CAB0();

case_0: {
        register s32 tail_result ASM_REG("$2") = 0;
        FIELD(arg0, s8, 0x9A) = var_v0;
        func_800A9A0C(base);
        tail_result = 0;
        ASM_TAILSLOT_PIN(tail_result);
        func_8016CAE8();
        return tail_result;
    }

case_2: {
        register s32 tail_result ASM_REG("$2") = 0;
        register s32 call_a1 ASM_REG("$5") = arg1;
        register s32 call_a2 ASM_REG("$6") = arg2;
        register void *call_a3 ASM_REG("$7") = base;
        ASM_KEEP(case2_a0);
        ASM_SCHED_BARRIER();
        ASM_KEEP(call_a1);
        ASM_KEEP(call_a2);
        ASM_KEEP(call_a3);
        func_8016BF74(case2_a0, call_a1, call_a2, call_a3);
        tail_result = 0;
        ASM_TAILSLOT_PIN(tail_result);
        func_8016CAE8();
        return tail_result;
    }

case_1:
    FIELD(base, u8, 0x71) &= 0x7F;
    if ((func_800A2BDC(base) << 16) != 0) {
        goto block_clear;
    }

block_tail:
    FIELD(base, u8, 0x71) &= 0x7F;
    var_v0 = 1;
    if (!(D_80083462 & 8)) {
        return var_v0;
    }

block_clear:
    var_v0 = 0;
    FIELD(base, u16, 0x46) &= 0x7FFF;
    return var_v0;
}

/* MECHANISM: A distinct base=arg0 live range yields retail's 0x30 frame and s1/s2/s3/s0/s4 roles.
   Lexical state-case labels plus the s16 call result reproduce the switch CFG and v1 sign extension.
   Zero-arg noreturn dispatcher typing and guarded tail-slot pins form each retail j delay slot. */
