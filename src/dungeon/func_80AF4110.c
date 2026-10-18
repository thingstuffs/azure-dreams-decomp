#include "modules/dungeon_resource10_slot0.h"

void func_80175910(Resource10CallbackState *state, void *motion, void *position, void *actor)
{
    if (resolve_actor_floor_trap_once(state, motion, position, actor) > 0) {
        state->callback = func_801717F4;
    }
}
