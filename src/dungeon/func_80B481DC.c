#include "modules/dungeon_resource12_slot0.h"

void func_801759DC(Resource12CallbackState *state, void *motion, void *position, void *actor)
{
    if (resolve_actor_floor_trap_once(state, motion, position, actor) > 0) {
        state->callback = update_actor_state_and_select_target;
    }
}
