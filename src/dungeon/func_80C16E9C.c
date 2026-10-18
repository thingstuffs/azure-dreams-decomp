#include "modules/dungeon_resource17_slot0.h"

void func_8017269C(Resource17CallbackState *state, void *entity, void *position, void *graphic)
{
    if (update_linked_actor_motion(state, entity, position, graphic)) {
        if ((s16)check_actor_floor_trap(position, graphic) > 0) {
            state->callback = update_entity_movement_and_ground_height;
        }
    }
}
