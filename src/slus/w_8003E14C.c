#include "common.h"

extern u8 D_80082E6A;

/* Return the current value capped at 40 when the mode is 2, or zero otherwise. */
s32 func_8003E14C(void)
{
    if (D_80082E6A == 2) {
        s32 capped_value = 0x28;
        s32 current_value = *(s16 *)0x8008146C;

        if (current_value < 0x29) {
            capped_value = current_value;
        }
        return capped_value;
    }
    return 0;
}
