#include "modules/dungeon_resource06_slot0.h"

void func_80173478(Resource06CallbackState *state, void *motion, void *position, void *actor)
{
    if (dungeonUpdateActorHopAndGrow(state, motion, position, actor)) {
        state->callback = func_8017140C;
    }
}
