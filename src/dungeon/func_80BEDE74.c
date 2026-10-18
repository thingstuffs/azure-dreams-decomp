#include "modules/dungeon_resource16_slot0.h"

void func_80173674(Resource16CallbackState *state, void *motion, void *position, void *actor)
{
    if (resolve_actor_floor_trap_once(state, motion, position, actor) > 0) {
        state->callback = update_actor_state_and_dispatch_transition;
    }
}
