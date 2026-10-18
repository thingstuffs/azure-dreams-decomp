/* Relink of matched dungeon/func_809CC43C; every changed retail word is a paired relocation. */
#define func_80170E54 func_80159400
#include "modules/dungeon_resource03_slot0.h"

void func_8015D108(Resource03CallbackState *state, void *motion, void *position, void *actor)
{
    if (propagate_actor_action_flag(state, motion, position, actor) > 0) {
        state->callback = func_80159400;
    }
}
