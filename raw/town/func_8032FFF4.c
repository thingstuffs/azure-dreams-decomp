#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((s8 *)(ptr) + (offset)))

extern s8 D_80016000[];

void func_8001A7F4(s32 arg0, s32 arg1, s32 arg2)
{
    register void *base ASM_REG("$4");
    register void *dst ASM_REG("$7");

    (void)arg0;
    base = *(void **)D_80016000;
    dst = FIELD(base, void *, 0x1C);
    ASM_KEEP(dst);
    arg1 <<= 6;
    FIELD(dst, s32, 4) = arg1 / 10 + 0x220;
    base = FIELD(base, void *, 0x1C);
    ASM_KEEP(base);
    arg2 <<= 6;
    FIELD(base, s32, 8) = arg2 / 10 + 0x220;
}

/* MECHANISM: Frameless leaf with the global base held in a0 and the first
   destination in a3; scaled coordinates remain in their a1/a2 ABI registers.
   The portable /10 form is byte-exact when sched2 is disabled, preventing its
   repeated sign-shift hoist across mfhi and the quotient shift. */
