#include "modules/dungeon_resource03_slot0.h"

void dungeonFadeEntityColorsToNeutral(Resource03CallbackState *state, void *motion, void *position, void *actor)
{
    if (dungeonUpdateSpinningActorFall(state, motion, position, actor)) {
        state->callback = func_80170E54;
    }
}
