#include "modules/dungeon_resource08_slot0.h"

void func_80174BBC(Resource08CallbackState *state, void *motion, void *position, void *actor)
{
    if (resolve_actor_floor_trap_once(state, motion, position, actor) > 0) {
        state->callback = update_actor_behavior_and_effect;
    }
}
