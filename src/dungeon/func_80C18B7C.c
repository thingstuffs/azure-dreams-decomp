#include "modules/dungeon_resource17_slot0.h"

void func_8017437C(Resource17CallbackState *state, void *motion, void *position, void *actor)
{
    if (dungeonInterpolateActorToTerrainTile(state, motion, position, actor)) {
        state->callback = func_801713A8;
    }
}
