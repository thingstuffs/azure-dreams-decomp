#include "modules/dungeon_resource07_slot0.h"

void func_80174020(Resource07CallbackState *state, void *motion, void *position, void *actor)
{
    if (interpolate_actor_to_terrain_tile(state, motion, position, actor)) {
        state->callback = func_80170E54;
    }
}
