#include "modules/dungeon_resource16_slot0.h"

void func_80173530(Resource16CallbackState *state, void *entity, void *position, void *graphic)
{
    if (update_thrown_actor_travel(state, entity, position, graphic)) {
        if ((s16)check_actor_floor_trap(position, graphic) > 0) {
            state->callback = update_actor_state_and_dispatch_transition;
        }
    }
}
