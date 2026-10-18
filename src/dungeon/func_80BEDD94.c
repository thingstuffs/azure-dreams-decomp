#include "modules/dungeon_resource16_slot0.h"

void func_80173594(Resource16CallbackState *state, void *motion, void *position, void *actor)
{
    if (interpolate_actor_to_terrain_tile(state, motion, position, actor)) {
        state->callback = update_actor_state_and_dispatch_transition;
    }
}
