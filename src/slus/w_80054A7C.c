#include "common.h"

/* Dispatches on the low byte of a0: ==3 -> func_800540A8(); ==4 -> func_800541E8();
   ==1 or ==2 -> func_80055B44(a0 & 0xFFFF) using the ORIGINAL (unmasked) a0; ==0 or >=5 -> no-op. */
extern void func_800540A8(void);
extern void func_800541E8(void);
extern void func_80055B44(s32 a0);

void func_80054A7C(s32 a0) {
    register s32 v1 ASM_REG("$3") = a0;   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    a0 = a0 & 0xFF;
    if (a0 == 3) {
        goto case3;
    }
    if (a0 < 4) {
        goto rangelow;
    }
    if (a0 == 4) {
        goto case4;
    }
    goto end;
rangelow:
    if (a0 == 0) {
        goto end;
    }
    func_80055B44(v1 & 0xFFFF);
    goto end;
case3:
    func_800540A8();
    goto end;
case4:
    func_800541E8();
end:
    return;
}
