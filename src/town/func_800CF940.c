#include "common.h"

extern void townMoveFlagObjectUntilTimerExpiry(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);

/* Advance the object's timed movement with duration 16 and step (-8, 0). */
void townMoveFlagObjectByStep16Minus8(s32 state, s32 obj, s32 unused) {
    townMoveFlagObjectUntilTimerExpiry(state, obj, unused, 0x10, -8, 0);
}
