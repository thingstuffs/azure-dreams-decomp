#include "modules/dungeon_resource06_slot0.h"

void func_80175834(Resource06CallbackState *state, void *motion, void *position, void *actor)
{
    if (propagate_actor_action_flag(state, motion, position, actor) > 0) {
        state->callback = initialize_destination_state;
    }
}
