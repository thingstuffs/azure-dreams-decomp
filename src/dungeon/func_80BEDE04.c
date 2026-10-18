#include "modules/dungeon_resource16_slot0.h"

void func_80173604(Resource16CallbackState *state, void *motion, void *position, void *actor)
{
    if (propagate_actor_action_flag(state, motion, position, actor)) {
        state->callback = update_actor_state_and_dispatch_transition;
    }
}
