#include "modules/dungeon_resource16_slot0.h"

void func_801735CC(Resource16CallbackState *state, void *motion, void *position, void *actor)
{
    if (update_spinning_actor_fall(state, motion, position, actor)) {
        state->callback = update_actor_state_and_dispatch_transition;
    }
}
