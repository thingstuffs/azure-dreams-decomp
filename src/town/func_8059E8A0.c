#include "common.h"

extern s32 func_80018964(s32);

/* Return whether both checks for 0x1200 and 0x1201 return zero. */
s32 func_800168A0(void) {
    s32 result;
    register s32 return_value ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */

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
