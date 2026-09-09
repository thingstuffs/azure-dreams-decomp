#include "common.h"

extern s16 func_8009FB34(s32, s32);
extern u16 D_8006CCD8[];
extern u16 D_8006CCE8[];

s32 func_8009FFD4(u8 *arg0, s16 *arg1) {
    s32 i = 0;
    s32 rv;
    u16 *x = D_8006CCE8;
    u16 *y = D_8006CCD8;
    do {
        s16 result;

        result = func_8009FB34((arg0[0x24] + *y) & 0xFFFF, (arg0[0x25] + *x) & 0xFFFF);
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        x++;
        if (result >= 0) {
            goto next;
        }
        *arg1 = i << 9;
        rv = 1;
        goto done;
next:
        i++;
        y++;
    } while (i < 8);
    rv = 0;
done:
    ASM_KEEP(rv); /* MATCH: merge both return values before the shared epilogue. */
    return rv;
}

/* MECHANISM: The two symbol bases stay live as s2/s1, producing the 0x28 frame and
   retail save order; explicit nonnegative continuation makes failure fall through.
   A post-call scheduler barrier places unconditional x++ in the bgez delay; noreturn plus
   tail-slot pin emits j/return-1, and final v0 keep parks return 0 before restores. */
