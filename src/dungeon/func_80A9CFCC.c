#include "modules/dungeon_resource08_slot0.h"

void advance_a_timed_actor_animation_applies_completion_effects(Resource08CallbackState *state, void *entity, void *position, void *graphic)
{
    if (update_linked_actor_motion(state, entity, position, graphic)) {
        if ((s16)check_actor_floor_trap(position, graphic) > 0) {
            state->callback = update_actor_behavior_and_effect;
        }
    }
}
