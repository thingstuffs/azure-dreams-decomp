#include "modules/dungeon_resource03_slot0.h"

void func_801725BC(Resource03CallbackState *state, void *entity, void *position, void *graphic)
{
    if (update_linked_actor_motion(state, entity, position, graphic)) {
        if ((s16)check_actor_floor_trap(position, graphic) > 0) {
            state->callback = func_80170E54;
        }
    }
}
