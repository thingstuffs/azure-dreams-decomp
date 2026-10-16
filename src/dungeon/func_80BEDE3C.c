#include "modules/dungeon_resource16_slot0.h"

void func_8017363C(Resource16CallbackState *state, void *motion, void *position, void *actor)
{
    if (dungeonUpdateActorFadeIn(state, motion, position, actor)) {
        state->callback = func_80171014;
    }
}
