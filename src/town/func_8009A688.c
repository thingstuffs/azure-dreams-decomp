#include "common.h"

typedef void (*Callback)(s32, void *, void *, void *);

extern s32 func_800352FC(void);
extern void func_80097E7C(s32, void *, void *);
extern s32 *D_800D0508[];
extern s32 *D_800FE5D8[3];

void func_80097DE8(s32 arg0, void *arg1, void *arg2) {
    register void *carrier ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    u8 *state;
    s32 call_arg0;
    void *call_arg1;
    void *call_arg2;
    Callback callback;
    s8 status;

    if (func_800352FC() == 0) {
        call_arg0 = arg0;
        call_arg1 = arg1;
        carrier = D_800FE5D8[0];
        ASM_KEEP(carrier);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        call_arg2 = arg2;
        func_80097E7C(call_arg0, call_arg1, call_arg2);
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        return;
    }

    carrier = (void *)0x80080000;
    ASM_KEEP(carrier);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    state = (u8 *)carrier + 0x2660;
    ASM_KEEP(state);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    status = *(s8 *)(state + 8);
    if (status >= 2) {
        call_arg0 = arg0;
        call_arg1 = arg1;
        carrier = D_800D0508;
        ASM_KEEP(carrier);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        carrier = ((void **)carrier)[status];
        ASM_KEEP(carrier);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        call_arg2 = arg2;
        func_80097E7C(call_arg0, call_arg1, call_arg2);
        return;
    }

    if (status < 0) {
        call_arg0 = arg0;
        call_arg1 = arg1;
        carrier = D_800FE5D8[0];
        ASM_KEEP(carrier);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        callback = (Callback)carrier;
        call_arg2 = arg2;
        ASM_KEEP(call_arg2);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        *(s8 *)(state + 8) = 0;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        callback(call_arg0, call_arg1, call_arg2, state);
    }
}

/* MECHANISM: The three incoming args stay in s0/s1/s2 under the retail 0x20 frame, while
   a guarded v0 carrier selects each shared tail and a3 holds the 0x80082660 state base.
   Branch-local a0/a1 lifetimes expose retail's delay fills; the final v0 load holds a2
   in its load-delay slot and a scheduling barrier keeps the byte store before jalr. */
