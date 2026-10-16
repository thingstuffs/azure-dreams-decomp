#include "modules/dungeon_resource10_slot0.h"

void dungeonCreatePositionedSpriteEffect(Resource10CallbackState *state, void *motion, void *position, void *actor)
{
    if (dungeonUpdateSpinningActorFall(state, motion, position, actor)) {
        state->callback = func_801717F4;
    }
}
