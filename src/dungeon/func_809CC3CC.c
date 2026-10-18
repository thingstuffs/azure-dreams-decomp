#include "modules/dungeon_resource03_slot0.h"

void func_80173BCC(Resource03CallbackState *state, void *motion, void *position, void *actor)
{
    if (update_actor_fade_in(state, motion, position, actor)) {
        state->callback = func_80170E54;
    }
}
