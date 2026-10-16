#include "modules/dungeon_resource17_slot0.h"

void func_801743B4(Resource17CallbackState *state, void *motion, void *position, void *actor)
{
    if (dungeonUpdateSpinningActorFall(state, motion, position, actor)) {
        state->callback = func_801713A8;
    }
}
