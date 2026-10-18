#include "modules/dungeon_resource03_slot0.h"

void func_80173AF8(Resource03CallbackState *state, void *entity, void *position, void *graphic)
{
    if (update_thrown_actor_travel(state, entity, position, graphic)) {
        if ((s16)check_actor_floor_trap(position, graphic) > 0) {
            state->callback = func_80170E54;
        }
    }
}
