#include "modules/dungeon_resource10_slot0.h"

void func_80174384(Resource10CallbackState *state, void *motion, void *position, void *actor)
{
    if (interpolate_actor_to_terrain_tile(state, motion, position, actor)) {
        state->callback = func_801717F4;
    }
}
