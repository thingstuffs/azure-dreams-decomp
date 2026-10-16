#include "modules/dungeon_resource17_slot0.h"

void dungeonBlendAnimationPaletteAndComplete(Resource17CallbackState *state, void *motion, void *position, void *actor)
{
    if (dungeonResolveActorFloorTrapOnce(state, motion, position, actor) > 0) {
        state->callback = func_801713A8;
    }
}
