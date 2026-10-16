#include "modules/dungeon_resource08_slot0.h"

void func_8017404C(Resource08CallbackState *state, void *motion, void *position, void *actor)
{
    if (dungeonInterpolateActorToTerrainTile(state, motion, position, actor)) {
        state->callback = dungeonUpdateActorBehaviorAndEffect;
    }
}
