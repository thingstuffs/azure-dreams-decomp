#include "modules/dungeon_resource12_slot0.h"

void func_80175A14(Resource12CallbackState *state, void *motion, void *position, void *actor)
{
    if (func_800AC7EC(state, motion, position, actor) > 0) {
        state->callback = func_80170E70;
    }
}
