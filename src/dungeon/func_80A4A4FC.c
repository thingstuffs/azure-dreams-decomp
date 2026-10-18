#include "modules/dungeon_resource06_slot0.h"

void create_randomized_rotated_effect(Resource06CallbackState *state, void *entity, void *position, void *graphic)
{
    if (update_thrown_actor_travel(state, entity, position, graphic)) {
        if ((s16)check_actor_floor_trap(position, graphic) > 0) {
            state->callback = initialize_destination_state;
        }
    }
}
