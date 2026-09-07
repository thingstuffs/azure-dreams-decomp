#include "common.h"

extern s32 func_800990FC(void);
extern s32 func_80099194(void *, s32);
extern s32 func_80099290(s32);
extern s32 func_80099734(void *, s32);
extern void func_800A5720(s32);
extern void func_80176398() __attribute__((noreturn));

extern u8 D_800E1F7B[];
extern u8 D_800E1F93[];
extern u8 D_8017088C[];

void func_80E12B30(s32 arg0, void *arg1) {
    s32 result;

    result = func_800990FC();
    if (arg0 << 16) {
        register void *dispatch_arg ASM_REG("$4");

        func_80099734(arg1, result);
        dispatch_arg = D_800E1F7B;
        ASM_TAILSLOT_PIN(dispatch_arg);
        func_80176398();
        return;
    }

    func_80099290(func_80099194(D_8017088C,
        func_80099734(arg1, func_80099194(D_800E1F93, result))));
    func_800A5720(result);
}

/* MECHANISM: The seed fixes the 0x20 frame and s0/s2/ra/s1 save order, with result held in s1.
   A guarded $a0 dispatch_arg plus ASM_TAILSLOT_PIN separates the low half from the noreturn call.
   LEAD 18 converts jal to j; LEAD 28b sinks the low half into its delay slot, closing word 15. */
