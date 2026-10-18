#include "modules/dungeon_resource16_slot0.h"

void func_8017238C(Resource16CallbackState *state, void *entity, void *position, void *graphic)
{
    if (update_linked_actor_motion(state, entity, position, graphic)) {
        if ((s16)check_actor_floor_trap(position, graphic) > 0) {
            state->callback = update_actor_state_and_dispatch_transition;
        }
    }
}
