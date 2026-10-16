#include "modules/dungeon_resource16_slot0.h"

void func_80173594(Resource16CallbackState *state, void *motion, void *position, void *actor)
{
    if (dungeonInterpolateActorToTerrainTile(state, motion, position, actor)) {
        state->callback = func_80171014;
    }
}
