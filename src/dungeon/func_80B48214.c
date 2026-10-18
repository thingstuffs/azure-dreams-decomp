#include "modules/dungeon_resource12_slot0.h"

void func_80175A14(Resource12CallbackState *state, void *motion, void *position, void *actor)
{
    if (propagate_actor_action_flag(state, motion, position, actor) > 0) {
        state->callback = update_actor_state_and_select_target;
    }
}
