#include "modules/dungeon_resource10_slot0.h"

void advance_boss_command_stream(Resource10CallbackState *state, void *entity, void *position, void *graphic)
{
    if (update_thrown_actor_travel(state, entity, position, graphic)) {
        if ((s16)check_actor_floor_trap(position, graphic) > 0) {
            state->callback = func_801717F4;
        }
    }
}
