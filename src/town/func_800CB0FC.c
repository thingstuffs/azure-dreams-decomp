#include "common.h"
#include "m2c_compat.h"

void townCreateTimedEffectObject(s32, s32, s32);                            /* extern */
void townMovePositionTowardTarget();       /* extern */

/* Run both object handlers with the supplied state and context. */
void func_800C885C(s32 object, s32 state, s32 context) {
    townCreateTimedEffectObject(object, state, context);
    townMovePositionTowardTarget(object, state, context);
}
