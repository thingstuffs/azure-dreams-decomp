#include "modules/dungeon_resource07_slot0.h"

void func_801736BC(Resource07CallbackState *state, void *motion, void *position, void *actor)
{
    if (dungeonUpdateActorHopAndGrow(state, motion, position, actor)) {
        state->callback = func_80170E54;
    }
}
