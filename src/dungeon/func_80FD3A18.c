/* Relink of matched dungeon/func_80C18C5C; every changed retail word is a paired relocation. */
#define func_801713A8 func_80152F6C
#include "modules/dungeon_resource17_slot0.h"

void func_80157218(Resource17CallbackState *state, void *motion, void *position, void *actor)
{
    if (dungeonPropagateActorActionFlag(state, motion, position, actor) > 0) {
        state->callback = func_80152F6C;
    }
}
