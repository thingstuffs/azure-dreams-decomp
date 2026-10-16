#include "modules/dungeon_resource07_slot0.h"

void func_80174058(Resource07CallbackState *state, void *motion, void *position, void *actor)
{
    if (func_800AC5C8(state, motion, position, actor)) {
        state->callback = func_80170E54;
    }
}
