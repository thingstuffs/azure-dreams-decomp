/* Relink of matched dungeon/func_80A74900; every changed retail word is a paired relocation. */
#define func_80170E54 func_80152E54
#include "modules/dungeon_resource07_slot0.h"

void func_80156100(Resource07CallbackState *state, void *motion, void *position, void *actor)
{
    if (propagate_actor_action_flag(state, motion, position, actor) > 0) {
        state->callback = func_80152E54;
    }
}
