#include "common.h"
#include "shared/entity.h"
#include "m2c_compat.h"
#include "town/player.h"

/* extern */

/* Runs the fallback if the value is unchanged and both state fields are zero. */
void run_action_then_fallback_on_no_change(s32 *value, ObjectPosition *state, s32 context) {
    s32 old_value;

    old_value = *value;
    dispatch_actor_interaction_actions(value, state, context);
    if ((old_value == *value) && (state->velocity_x == 0) && (state->velocity_y == 0)) {
        initialize_scene_action_record(value, state, context);
    }
}
