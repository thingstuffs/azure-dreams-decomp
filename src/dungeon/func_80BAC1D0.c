/* Relink of matched dungeon/func_80BEDE04; every changed retail word is a paired relocation. */
#define func_80171014 func_8015EE9C
#include "modules/dungeon_resource16_slot0.h"

void func_801619D0(Resource16CallbackState *state, void *motion, void *position, void *actor)
{
    if (dungeonPropagateActorActionFlag(state, motion, position, actor)) {
        state->callback = func_8015EE9C;
    }
}
