/* Relink of matched dungeon/func_80BEDE04; every changed retail word is a paired relocation. */
#define func_80171014 func_8014D014
#include "modules/dungeon_resource16_slot0.h"

void func_8014F604(Resource16CallbackState *state, void *motion, void *position, void *actor)
{
    if (dungeonPropagateActorActionFlag(state, motion, position, actor)) {
        state->callback = func_8014D014;
    }
}
