#include "common.h"
#include "shared/entity.h"
#include "engine/effect.h"
#include "engine/entity.h"

/* Scales the current value between two bounds, capping the result at 20. */
s32 calc_gauge_fill(ActorRecord *state)
{
    s32 lower;
    s32 upper;
    s32 range;

    lower = lookup_level_experience_threshold(state, -1);
    upper = lookup_level_experience_threshold(state, 0);
    range = upper - lower;
    lower = state->experience - lower;
    range = (lower * 20) / range;
    if (range >= 21) {
        range = 20;
    }
    return range;
}
