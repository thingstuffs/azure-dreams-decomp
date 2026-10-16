#include "modules/dungeon_resource17_slot0.h"

void func_8017445C(Resource17CallbackState *state, void *motion, void *position, void *actor)
{
    if (dungeonPropagateActorActionFlag(state, motion, position, actor) > 0) {
        state->callback = func_801713A8;
    }
}
