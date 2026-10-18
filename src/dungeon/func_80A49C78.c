#include "modules/dungeon_resource06_slot0.h"

void func_80173478(Resource06CallbackState *state, void *motion, void *position, void *actor)
{
    if (update_actor_hop_and_grow(state, motion, position, actor)) {
        state->callback = initialize_destination_state;
    }
}
