#include "modules/dungeon_resource10_slot0.h"

void create_positioned_sprite_effect(Resource10CallbackState *state, void *motion, void *position, void *actor)
{
    if (update_spinning_actor_fall(state, motion, position, actor)) {
        state->callback = func_801717F4;
    }
}
