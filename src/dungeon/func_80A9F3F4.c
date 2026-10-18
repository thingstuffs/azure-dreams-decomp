#include "modules/dungeon_resource08_slot0.h"

void func_80174BF4(Resource08CallbackState *state, void *motion, void *position, void *actor)
{
    if (propagate_actor_action_flag(state, motion, position, actor) > 0) {
        state->callback = update_actor_behavior_and_effect;
    }
}
