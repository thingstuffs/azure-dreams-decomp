#include "common.h"

#define FIELD(expr, type, offset) (*(type *)((s8 *)(expr) + (offset)))

extern s32 func_80017EA0();
extern s32 func_80017F44(void) __attribute__((noreturn));
extern s32 D_80019BB0;
extern s32 D_80019BB4;

s32 func_80017EF0(void *arg0, s32 arg1) {
    s32 result;

    if (D_80019BB0 == 3) {
        result = 0;
        ASM_TAILSLOT_PIN(result);
        return func_80017F44();
    }
    FIELD((arg1 * 0x10) + FIELD(arg0, s32, 0x10), s32, 8) =
        func_80017EA0(D_80019BB4);
    return 1;
}

/* MECHANISM: Preserved the seed's 0x20 frame, s0/s1 argument holds, and early noreturn CFG.
   A guarded $v0 pin materializes zero; ASM_TAILSLOT_PIN lets LEAD 28b sink it into
   the LEAD 18-converted tail-j delay slot, closing retail word 11. */
