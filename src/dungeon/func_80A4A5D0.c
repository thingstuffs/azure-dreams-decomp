#include "modules/dungeon_resource06_slot0.h"

void func_80173DD0(Resource06CallbackState *state, void *motion, void *position, void *actor)
{
    if (update_actor_fade_in(state, motion, position, actor)) {
        state->callback = initialize_destination_state;
    }
}
