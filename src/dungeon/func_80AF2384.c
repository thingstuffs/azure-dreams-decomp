#include "modules/dungeon_resource10_slot0.h"

void func_80173B84(Resource10CallbackState *state, void *motion, void *position, void *actor)
{
    if (update_actor_hop_and_grow(state, motion, position, actor)) {
        state->callback = func_801717F4;
    }
}
