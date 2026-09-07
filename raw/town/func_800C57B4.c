#include "common.h"

extern u8 D_80083160[];
void func_800C2F80();

s32 func_800C2F14(s32 arg0, s16 arg1) {
    u8 *base;
    s16 step;
    s32 shifted_arg1;
    s32 signed_arg1;
    s32 distance;
    register s32 result ASM_REG("$2");

    base = D_80083160;
    ASM_KEEP(base);
    shifted_arg1 = arg1 << 16;
    signed_arg1 = shifted_arg1 >> 16;
    result = signed_arg1 < 2;
    if (result) {
        ASM_SCHED_BARRIER();
        return 0;
    }

    result = 0x1000;
    step = (s16)(result / signed_arg1);
    distance = (*(s16 *)(base + 0xC8) + (step / 2) - arg0) & 0xFFF;
    distance /= step;
    result = (signed_arg1 / 2) < distance;
    ASM_TAILSLOT_PIN_TIED(result);
    func_800C2F80(step, shifted_arg1, signed_arg1, arg0);
    return result;
}

/* MECHANISM: A kept global-base local plus named shifted/signed arguments gives
   the retail argument lifetimes; one pinned $v0 carries guard, numerator, and result.
   A taken-block scheduler fence preserves li 0x1000 in the branch delay, while
   LEAD 19/22/28 remove the frame and sink the final slt into the tail-j slot. */
