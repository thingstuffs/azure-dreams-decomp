#include "common.h"

extern s32 func_800990FC(void);
extern s32 func_80099194(void *, s32);
extern void func_80099290(s32);
extern s32 func_80099734(s32, s32);
extern void func_800A5720(s32);
extern void func_801762FC(void) __attribute__((noreturn));

extern u8 D_800E1F65[9];
extern u8 D_800E1FB9[9];

void func_80E12AA4(s32 arg0, s32 arg1)
{
    s32 value;
    register void *dispatch_arg ASM_REG("$4");

    value = func_800990FC();
    if (arg0 << 16) {
        func_80099734(arg1, value);
        dispatch_arg = D_800E1FB9;
        ASM_TAILSLOT_PIN(dispatch_arg);
        func_801762FC();
        return;
    }
    func_80099290(func_80099194(D_800E1F65,
                                func_80099734(arg1, value)));
    func_800A5720(value);
}

/* MECHANISM: The aligned-1 seed already fixed the 0x20 frame and s0/s2/ra/s1 save order.
   A guarded short-lived $a0 carrier makes func_801762FC a zero-arg noreturn tail.
   LEAD 18 flips jal to j; LEAD 28 sinks the carrier addiu into its delay slot. */
