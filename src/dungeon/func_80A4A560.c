#include "modules/dungeon_resource06_slot0.h"

void func_80173D60(Resource06CallbackState *state, void *motion, void *position, void *actor)
{
    if (interpolate_actor_to_terrain_tile(state, motion, position, actor)) {
        state->callback = initialize_destination_state;
    }
}
