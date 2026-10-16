#include "modules/dungeon_resource10_slot0.h"

void func_801743F4(Resource10CallbackState *state, void *motion, void *position, void *actor)
{
    if (dungeonUpdateActorFadeIn(state, motion, position, actor)) {
        state->callback = func_801717F4;
    }
}
