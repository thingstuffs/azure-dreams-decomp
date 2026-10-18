#include "modules/dungeon_resource08_slot0.h"

void func_801736E8(Resource08CallbackState *state, void *motion, void *position, void *actor)
{
    if (update_actor_hop_and_grow(state, motion, position, actor)) {
        state->callback = update_actor_behavior_and_effect;
    }
}
