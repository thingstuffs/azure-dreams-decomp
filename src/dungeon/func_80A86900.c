/* Relink of matched dungeon/func_80A74900; every changed retail word is a paired relocation. */
#define func_80170E54 func_8015EE54
#include "modules/dungeon_resource07_slot0.h"

void func_80162100(Resource07CallbackState *state, void *motion, void *position, void *actor)
{
    if (dungeonPropagateActorActionFlag(state, motion, position, actor) > 0) {
        state->callback = func_8015EE54;
    }
}
