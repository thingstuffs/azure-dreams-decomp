/* Relink of matched dungeon/func_80BEDE04; every changed retail word is a paired relocation. */
#include "modules/dungeon_resource16_slot0.h"
extern void func_8016B014(void *, void *, void *, void *);

void func_8016D604(Resource16CallbackState *state, void *motion, void *position, void *actor)
{
    if (propagate_actor_action_flag(state, motion, position, actor)) {
        state->callback = func_8016B014;
    }
}
