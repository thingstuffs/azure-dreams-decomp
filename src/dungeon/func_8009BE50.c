#include "common.h"
extern u8 D_800E3DB0[];
s32 func_800A15B0(s16 arg0) {
    s16 value = arg0;
    u8 *p = D_800E3DB0;
    s16 i = 0;
    register s16 next ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */
    if (arg0 == 0x39) value = 2;
    do {
        if (p[1] != value) {
            next = i + 1;
            ASM_KEEP(next);   /* MATCH pin: retail register colouring depends on it */
            i = next;
            p += 8;
        } else {
            return 1;
        }
    } while (next < 6);
    ASM_KEEP(i);   /* MATCH pin: retail register colouring depends on it */
    return 0;
}
/* MECHANISM: cdk-G0 split-la plus inequality fall-through exposes frameless LEAD-19/22 tail conversion.
   Zero-arg dispatch preserves a0/a1/a2; pinned sibling i(v1)/next(v0) locals reproduce the counter web. */
