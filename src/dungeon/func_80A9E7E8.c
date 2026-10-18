#include "modules/dungeon_resource08_slot0.h"

void func_80173FE8(Resource08CallbackState *state, void *entity, void *position, void *graphic)
{
    if (update_thrown_actor_travel(state, entity, position, graphic)) {
        if ((s16)check_actor_floor_trap(position, graphic) > 0) {
            state->callback = update_actor_behavior_and_effect;
        }
    }
}
