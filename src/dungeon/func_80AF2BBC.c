#include "modules/dungeon_resource10_slot0.h"

void func_801743BC(Resource10CallbackState *state, void *motion, void *position, void *actor)
{
    if (func_800AC5C8(state, motion, position, actor)) {
        state->callback = func_801717F4;
    }
}
