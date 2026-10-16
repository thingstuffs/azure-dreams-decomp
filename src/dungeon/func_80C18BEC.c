#include "modules/dungeon_resource17_slot0.h"

void dungeonUpdateEffectTrajectoryAndSprite(Resource17CallbackState *state, void *motion, void *position, void *actor)
{
    if (dungeonUpdateActorFadeIn(state, motion, position, actor)) {
        state->callback = func_801713A8;
    }
}
