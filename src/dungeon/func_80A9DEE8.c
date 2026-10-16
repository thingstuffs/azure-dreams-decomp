#include "modules/dungeon_resource08_slot0.h"

void func_801736E8(Resource08CallbackState *state, void *motion, void *position, void *actor)
{
    if (func_800ABDBC(state, motion, position, actor)) {
        state->callback = func_80170E7C;
    }
}
