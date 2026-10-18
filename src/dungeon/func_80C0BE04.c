/* Relink of matched dungeon/func_80BEDE04; every changed retail word is a paired relocation. */
#define update_actor_state_and_dispatch_transition func_80153014
#include "modules/dungeon_resource16_slot0.h"

void func_80155604(Resource16CallbackState *state, void *motion, void *position, void *actor)
{
    if (propagate_actor_action_flag(state, motion, position, actor)) {
        state->callback = func_80153014;
    }
}
