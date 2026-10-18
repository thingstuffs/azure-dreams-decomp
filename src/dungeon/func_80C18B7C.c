#include "modules/dungeon_resource17_slot0.h"

void func_8017437C(Resource17CallbackState *state, void *motion, void *position, void *actor)
{
    if (interpolate_actor_to_terrain_tile(state, motion, position, actor)) {
        state->callback = update_entity_movement_and_ground_height;
    }
}
