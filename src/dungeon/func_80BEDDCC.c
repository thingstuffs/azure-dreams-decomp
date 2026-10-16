#include "modules/dungeon_resource16_slot0.h"

void func_801735CC(Resource16CallbackState *state, void *motion, void *position, void *actor)
{
    if (func_800AC5C8(state, motion, position, actor)) {
        state->callback = func_80171014;
    }
}
