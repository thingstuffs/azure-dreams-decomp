#include "modules/dungeon_resource12_slot0.h"

void func_80173F00(Resource12CallbackState *state, void *motion, void *position, void *actor)
{
    if (update_actor_fade_in(state, motion, position, actor)) {
        state->callback = update_actor_state_and_select_target;
    }
}
