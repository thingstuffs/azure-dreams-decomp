#include "modules/dungeon_resource08_slot0.h"

void func_8017404C(Resource08CallbackState *state, void *motion, void *position, void *actor)
{
    if (func_800AC480(state, motion, position, actor)) {
        state->callback = func_80170E7C;
    }
}
