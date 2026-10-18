/* Relink of matched dungeon/func_80BEDE04; every changed retail word is a paired relocation. */
#include "modules/dungeon_resource16_slot0.h"
extern void func_801539DC(void *, void *, void *, void *);

void func_801565FC(Resource16CallbackState *state, void *motion, void *position, void *actor)
{
    if (propagate_actor_action_flag(state, motion, position, actor)) {
        state->callback = func_801539DC;
    }
}
