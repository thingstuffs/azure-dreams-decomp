#include "common.h"

extern void townMoveFlagObjectUntilTimerExpiry(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);

/* Forward three inputs with fixed parameters 16, 8, and -4. */
void townMoveFlagObjectByStep16Plus8Minus4(s32 input_first, s32 input_second, s32 input_third) {
    townMoveFlagObjectUntilTimerExpiry(input_first, input_second, input_third, 16, 8, -4);
}
