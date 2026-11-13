#include "common.h"
#include "shared/entity.h"
#include "m2c_compat.h"
#include "town/player.h"
#include "shared/sprite_frame_state.h"

/* extern */

/* Runs the fallback if the value is unchanged and both state fields are zero. */
void run_action_with_idle_fallback(s32 *value, ObjectPosition *state, SpriteFrameState *sprite) {
    s32 old_value;

    old_value = *value;
    dispatch_actor_interaction_actions(value, state, sprite);
    if ((old_value == *value) && (state->velocity_x == 0) && (state->velocity_y == 0)) {
        initialize_scene_action_record(value, state, sprite);
    }
}
