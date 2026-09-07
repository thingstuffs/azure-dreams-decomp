#include "common.h"

extern s16 func_8009FB34(s32, s32);
extern void func_800A0110(void) __attribute__((noreturn));
extern u16 D_8006CCD8[];
extern u16 D_8006CCE8[];

s32 func_800A0084(u8 *arg0, s16 *arg1) {
    s32 i = 0;
    u16 *x = D_8006CCE8;
    u16 *y = D_8006CCD8;
    do {
        s16 result;

        result = func_8009FB34((arg0[0x24] + *y) & 0xFFFF, (arg0[0x25] + *x) & 0xFFFF);
        ASM_SCHED_BARRIER();   /* MATCH pin: keeps a statement from moving across a call/branch */
        x++;
        if (result < 0) {
            goto next;
        }
        *arg1 = i << 9;
        {
            s32 rv;
            rv = 1;
            ASM_TAILSLOT_PIN(rv);   /* MATCH pin: retail delay-slot fill depends on it */
            func_800A0110();
            return rv;
        }
next:
        i++;
        y++;
    } while (i < 8);
    {
        s32 rv;
        rv = 0;
        ASM_KEEP(rv);   /* MATCH pin: retail schedule: same instructions, different order without it */
        return rv;
    }
}

/* MECHANISM: The two symbol bases stay live as s2/s1, producing the 0x28 frame and
   retail save order; explicit negative continuation makes success fall through.
   A post-call scheduler barrier places unconditional x++ in the bltz delay; noreturn plus
   tail-slot pin emits j/return-1, and final v0 keep parks return 0 before restores. */
