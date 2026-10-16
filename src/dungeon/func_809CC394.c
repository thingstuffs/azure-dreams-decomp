#include "modules/dungeon_resource03_slot0.h"

void func_80173B94(Resource03CallbackState *state, void *motion, void *position, void *actor)
{
    if (func_800AC5C8(state, motion, position, actor)) {
        state->callback = func_80170E54;
    }
}
