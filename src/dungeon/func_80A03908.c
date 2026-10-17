/* Relink of matched dungeon/func_809CC43C; every changed retail word is a paired relocation. */
#define func_80170E54 func_80165400
#include "modules/dungeon_resource03_slot0.h"

void func_80169108(Resource03CallbackState *state, void *motion, void *position, void *actor)
{
    if (dungeonPropagateActorActionFlag(state, motion, position, actor) > 0) {
        state->callback = func_80165400;
    }
}
