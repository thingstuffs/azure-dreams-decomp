#include "modules/dungeon_resource06_slot0.h"

void func_80172728(Resource06CallbackState *state, void *entity, void *position, void *graphic)
{
    if (update_linked_actor_motion(state, entity, position, graphic)) {
        if ((s16)check_actor_floor_trap(position, graphic) > 0) {
            state->callback = initialize_destination_state;
        }
    }
}
