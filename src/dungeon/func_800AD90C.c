#include "common.h"
#include "m2c_compat.h"

s32 dungeonUpdateActorHopAndShrink(void *, void *, void *);                            /* extern */

/* Forward the state, context, and data to dungeonUpdateActorHopAndShrink. */
void dungeonForwardActorEffectState(void *state, void *context, void *data) {
    dungeonUpdateActorHopAndShrink(state, context, data);
}
