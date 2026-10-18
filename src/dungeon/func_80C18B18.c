#include "modules/dungeon_resource17_slot0.h"

void update_timed_effect_and_expire(Resource17CallbackState *state, void *entity, void *position, void *graphic)
{
    if (update_thrown_actor_travel(state, entity, position, graphic)) {
        if ((s16)check_actor_floor_trap(position, graphic) > 0) {
            state->callback = update_entity_movement_and_ground_height;
        }
    }
}
