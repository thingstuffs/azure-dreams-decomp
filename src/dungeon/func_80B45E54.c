#include "modules/dungeon_resource12_slot0.h"

void func_80173654(Resource12CallbackState *state, void *motion, void *position, void *actor)
{
    if (dungeonUpdateActorHopAndGrow(state, motion, position, actor)) {
        state->callback = func_80170E70;
    }
}
