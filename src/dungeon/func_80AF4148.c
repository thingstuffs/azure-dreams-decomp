#include "modules/dungeon_resource10_slot0.h"

void func_80175948(Resource10CallbackState *state, void *motion, void *position, void *actor)
{
    if (propagate_actor_action_flag(state, motion, position, actor)) {
        state->callback = func_801717F4;
    }
}
