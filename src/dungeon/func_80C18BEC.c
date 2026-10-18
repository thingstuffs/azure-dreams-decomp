#include "modules/dungeon_resource17_slot0.h"

void update_effect_trajectory_and_sprite(Resource17CallbackState *state, void *motion, void *position, void *actor)
{
    if (update_actor_fade_in(state, motion, position, actor)) {
        state->callback = update_entity_movement_and_ground_height;
    }
}
