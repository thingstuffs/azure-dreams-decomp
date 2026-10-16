#include "modules/dungeon_resource17_slot0.h"

void func_801743EC(Resource17CallbackState *state, void *motion, void *position, void *actor)
{
    if (func_800ACE34(state, motion, position, actor)) {
        state->callback = func_801713A8;
    }
}
