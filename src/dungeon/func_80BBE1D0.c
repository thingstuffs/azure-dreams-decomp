/* Relink of matched dungeon/func_80BEDE04; every changed retail word is a paired relocation. */
#define update_actor_state_and_dispatch_transition func_8014CE9C
#include "modules/dungeon_resource16_slot0.h"

void func_8014F9D0(Resource16CallbackState *state, void *motion, void *position, void *actor)
{
    if (propagate_actor_action_flag(state, motion, position, actor)) {
        state->callback = func_8014CE9C;
    }
}
