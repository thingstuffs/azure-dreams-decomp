/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "shared/entity.h"
#include "m2c_compat.h"

void initialize_scene_action_record();      


void dispatch_actor_interaction_actions(s32 *, ObjectPosition *, s32);

void dispatch_actor_interaction_with_fallback(s32 *value, ObjectPosition *state, s32 context) {
    s32 old_value;

    old_value = *value;
    dispatch_actor_interaction_actions(value, state, context);
    if ((old_value == *value) && (state->velocity_x == 0) && (state->velocity_y == 0)) {
        initialize_scene_action_record(value, state, context);
    }
}
