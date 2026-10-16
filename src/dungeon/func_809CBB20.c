#include "modules/dungeon_resource03_slot0.h"

void func_80173320(Resource03CallbackState *state, void *motion, void *position, void *actor)
{
    if (dungeonUpdateActorHopAndGrow(state, motion, position, actor)) {
        state->callback = func_80170E54;
    }
}
