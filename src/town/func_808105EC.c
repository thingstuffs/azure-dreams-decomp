#include "common.h"

extern s16 func_8025E01C(void *);

// Advances the accumulator and resets it when clamping the stored value to a nonpositive bound.
void func_808105EC(void *unused, void *state)
{
    s32 upperBound;

    upperBound = func_8025E01C(state);
    if (upperBound > 0) {
        upperBound = 0;
    }

    *(s32 *)((u8 *)state + 0x14) += 0x1D000;
    if (upperBound < *(s16 *)((u8 *)state + 0xA)) {
        *(s16 *)((u8 *)state + 0xA) = upperBound;
        *(s32 *)((u8 *)state + 0x14) = 0;
    }
}
