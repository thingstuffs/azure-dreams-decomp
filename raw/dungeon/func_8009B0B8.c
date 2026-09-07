#include "common.h"

extern s32 func_80065F90();
extern s32 func_800A0880() __attribute__((noreturn));

s32 func_800A0818(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u16 *arg4) {
    s32 temp_v0;

    {
        s32 test_result;
        test_result = func_80065F90(arg3 - arg1, arg2 - arg0, arg2, arg3);
        temp_v0 = test_result;
        ASM_KEEP_NV(test_result);
        if ((test_result & 0x1FF) < 0x100) {
            goto in_range;
        }
    }
    {
        s32 tail_value;
        tail_value = *arg4 | 2;
        ASM_TAILSLOT_PIN_TIED(tail_value);
        return func_800A0880();
    }
in_range:
    *arg4 &= 0xFFFD;
    ASM_USE(temp_v0);
    return (temp_v0 + 0x100) & 0xE00;
}

/* MECHANISM: The 24-byte frame holds only arg4 in s0 across the first call.
   The out-of-range continuation consumes (*arg4 | 2) through its v0 ABI;
   the in-range path clears bit 1 and returns the wrapped 0xE00 component. */
