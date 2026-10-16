#include "modules/dungeon_resource16_slot0.h"

void func_80173604(Resource16CallbackState *state, void *motion, void *position, void *actor)
{
    if (func_800AC7EC(state, motion, position, actor)) {
        state->callback = func_80171014;
    }
}
