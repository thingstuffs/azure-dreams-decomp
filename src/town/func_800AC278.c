#include "common.h"

extern s32 func_800A98C4();
extern s32 func_800A98F8(s32 arg0);
extern s32 func_800A9970(s32 arg0);
extern void func_800A9A24();

s32 func_800A99D8(s32 arg0) {
    register s32 result ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */

    if (func_800A98C4() != 0) {
        return 3;
    }
    if (func_800A98F8(arg0) == 0) {
        result = func_800A9970(arg0);
        ASM_KEEP(result);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        if (result != 0) {
            return 2;
        }
        func_800A9A24();
        return 1;
    }
    {
        s32 zero_result;

        ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        zero_result = 0;
        return zero_result;
    }
}

/* MECHANISM: A 0x18 frame holds arg0 in the sole saved register s0 across calls.
   A v1-held call result preserves the explicit return copy; a guarded v0 zero
   block keeps the branch delay empty, and void-call + return 1 forms the sibcall. */
