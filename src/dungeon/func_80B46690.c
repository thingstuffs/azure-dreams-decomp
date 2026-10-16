#include "modules/dungeon_resource12_slot0.h"

void func_80173E90(Resource12CallbackState *state, void *motion, void *position, void *actor)
{
    if (dungeonInterpolateActorToTerrainTile(state, motion, position, actor)) {
        state->callback = func_80170E70;
    }
}
