#include "modules/dungeon_resource16_slot0.h"

void func_80172D18(Resource16CallbackState *state, void *motion, void *position, void *actor)
{
    if (update_actor_hop_and_grow(state, motion, position, actor)) {
        state->callback = update_actor_state_and_dispatch_transition;
    }
}
