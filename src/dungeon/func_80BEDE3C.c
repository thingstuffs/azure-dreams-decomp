#include "modules/dungeon_resource16_slot0.h"

void func_8017363C(Resource16CallbackState *state, void *motion, void *position, void *actor)
{
    if (update_actor_fade_in(state, motion, position, actor)) {
        state->callback = update_actor_state_and_dispatch_transition;
    }
}
