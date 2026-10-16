#include "modules/dungeon_resource17_slot0.h"

void func_801738A8(Resource17CallbackState *state, void *motion, void *position, void *actor)
{
    if (dungeonUpdateActorHopAndGrow(state, motion, position, actor)) {
        state->callback = func_801713A8;
    }
}
