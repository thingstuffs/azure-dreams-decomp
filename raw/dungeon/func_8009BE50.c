#include "common.h"
extern void func_800A1610(void);
extern u8 D_800E3DB0[];
s32 func_800A15B0(s16 arg0) {
    s16 value = arg0;
    u8 *p = D_800E3DB0;
    register s16 i ASM_REG("$3") = 0;
    register s16 next ASM_REG("$2");
    if (arg0 == 0x39) value = 2;
    do {
        if (p[1] != value) {
            next = i + 1;
            ASM_KEEP(next);
            i = next;
            p += 8;
        } else {
            func_800A1610();
            return 1;
        }
    } while (next < 6);
    ASM_KEEP(i);
    return 0;
}
/* MECHANISM: cdk-G0 split-la plus inequality fall-through exposes frameless LEAD-19/22 tail conversion.
   Zero-arg dispatch preserves a0/a1/a2; pinned sibling i(v1)/next(v0) locals reproduce the counter web. */
