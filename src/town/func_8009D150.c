#include "common.h"
/* Move the current value toward the target by the given divisor. */
s16 townApproachPlayerValue(s32 divisor, s16 current, s16 target)
{
    if (divisor != 0) {
        u32 current_shifted = (u32)current << 16;
        return (s16)(current + (((s32)target - ((s32)current_shifted >> 16)) / divisor));
    }
    return current;
}
