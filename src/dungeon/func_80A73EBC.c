#include "modules/dungeon_resource07_slot0.h"

void func_801736BC(Resource07CallbackState *state, void *motion, void *position, void *actor)
{
    if (update_actor_hop_and_grow(state, motion, position, actor)) {
        state->callback = func_80170E54;
    }
}
