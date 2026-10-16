#include "modules/dungeon_resource10_slot0.h"

void func_80174384(Resource10CallbackState *state, void *motion, void *position, void *actor)
{
    if (func_800AC480(state, motion, position, actor)) {
        state->callback = func_801717F4;
    }
}
