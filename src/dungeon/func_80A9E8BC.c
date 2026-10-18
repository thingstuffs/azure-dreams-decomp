#include "modules/dungeon_resource08_slot0.h"

void func_801740BC(Resource08CallbackState *state, void *motion, void *position, void *actor)
{
    if (update_actor_fade_in(state, motion, position, actor)) {
        state->callback = update_actor_behavior_and_effect;
    }
}
