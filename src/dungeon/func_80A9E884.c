#include "modules/dungeon_resource08_slot0.h"

void dungeonCreateFourDirectionalEffects(Resource08CallbackState *state, void *motion, void *position, void *actor)
{
    if (dungeonUpdateSpinningActorFall(state, motion, position, actor)) {
        state->callback = dungeonUpdateActorBehaviorAndEffect;
    }
}
