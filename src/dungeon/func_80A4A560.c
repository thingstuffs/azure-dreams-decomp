#include "modules/dungeon_resource06_slot0.h"

void func_80173D60(Resource06CallbackState *state, void *motion, void *position, void *actor)
{
    if (dungeonInterpolateActorToTerrainTile(state, motion, position, actor)) {
        state->callback = func_8017140C;
    }
}
