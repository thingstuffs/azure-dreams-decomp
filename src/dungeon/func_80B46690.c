#include "modules/dungeon_resource12_slot0.h"

void func_80173E90(Resource12CallbackState *state, void *motion, void *position, void *actor)
{
    if (interpolate_actor_to_terrain_tile(state, motion, position, actor)) {
        state->callback = update_actor_state_and_select_target;
    }
}
