#include "modules/dungeon_resource12_slot0.h"

void func_80173E2C(Resource12CallbackState *state, void *entity, void *position, void *graphic)
{
    if (update_thrown_actor_travel(state, entity, position, graphic)) {
        if ((s16)check_actor_floor_trap(position, graphic) > 0) {
            state->callback = update_actor_state_and_select_target;
        }
    }
}
