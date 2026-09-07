#include "common.h"

extern s32 func_80018964(s32);

s32 func_800168A0(void) {
    s32 result;
    register s32 return_value ASM_REG("$2");   /* MATCH pin: retail delay-slot fill depends on it */

    if (func_80018964(0x1200) != 0) {
        goto return_zero;
    }
    result = func_80018964(0x1201);
    return_value = 1;
    if (result == 0) {
        goto done;
    }
return_zero:
    return_value = 0;
done:
    return return_value;
}

/* MECHANISM: The call-shaped body naturally gives the 0x18 frame with only ra saved.
   A guarded v1 result preserves the retail copy after the second call.
   The shared zero-return label and schedule barrier retain the branch diamond,
   allowing li v0,1 in the beqz delay slot while blocking the zero-return steal. */
