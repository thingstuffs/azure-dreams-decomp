#include "modules/dungeon_resource16_slot0.h"

void func_80172D18(Resource16CallbackState *state, void *motion, void *position, void *actor)
{
    if (dungeonUpdateActorHopAndGrow(state, motion, position, actor)) {
        state->callback = func_80171014;
    }
}
