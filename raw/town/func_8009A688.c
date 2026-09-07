#include "common.h"

typedef void (*Callback)(s32, void *, void *, void *);

extern s32 func_800352FC(void);
extern void func_80097E7C(s32, void *, void *);
extern s32 *D_800D0508[];
extern s32 *D_800FE5D8[3];

void func_80097DE8(s32 arg0, void *arg1, void *arg2) {
    register void *carrier ASM_REG("$2");
    register u8 *state ASM_REG("$7");
    register s32 call_arg0 ASM_REG("$4");
    register void *call_arg1 ASM_REG("$5");
    register void *call_arg2 ASM_REG("$6");
    Callback callback;
    s8 status;

    if (func_800352FC() == 0) {
        call_arg0 = arg0;
        ASM_KEEP(call_arg0);
        call_arg1 = arg1;
        ASM_KEEP(call_arg1);
        carrier = D_800FE5D8[0];
        ASM_KEEP(carrier);
        call_arg2 = arg2;
        func_80097E7C(call_arg0, call_arg1, call_arg2);
        ASM_SCHED_BARRIER();
        return;
    }

    carrier = (void *)0x80080000;
    ASM_KEEP(carrier);
    state = (u8 *)carrier + 0x2660;
    ASM_KEEP(state);
    status = *(s8 *)(state + 8);
    if (status >= 2) {
        call_arg0 = arg0;
        ASM_KEEP(call_arg0);
        call_arg1 = arg1;
        ASM_KEEP(call_arg1);
        carrier = D_800D0508;
        ASM_KEEP(carrier);
        carrier = ((void **)carrier)[status];
        ASM_KEEP(carrier);
        call_arg2 = arg2;
        func_80097E7C(call_arg0, call_arg1, call_arg2);
        return;
    }

    if (status < 0) {
        call_arg0 = arg0;
        call_arg1 = arg1;
        ASM_KEEP(call_arg1);
        carrier = D_800FE5D8[0];
        ASM_KEEP(carrier);
        callback = (Callback)carrier;
        call_arg2 = arg2;
        ASM_KEEP(call_arg2);
        *(s8 *)(state + 8) = 0;
        ASM_SCHED_BARRIER();
        callback(call_arg0, call_arg1, call_arg2, state);
    }
}

/* MECHANISM: The three incoming args stay in s0/s1/s2 under the retail 0x20 frame, while
   a guarded v0 carrier selects each shared tail and a3 holds the 0x80082660 state base.
   Branch-local a0/a1 lifetimes expose retail's delay fills; the final v0 load holds a2
   in its load-delay slot and a scheduling barrier keeps the byte store before jalr. */
