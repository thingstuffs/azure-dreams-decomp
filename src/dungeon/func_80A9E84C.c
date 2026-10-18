#include "modules/dungeon_resource08_slot0.h"

void func_8017404C(Resource08CallbackState *state, void *motion, void *position, void *actor)
{
    if (interpolate_actor_to_terrain_tile(state, motion, position, actor)) {
        state->callback = update_actor_behavior_and_effect;
    }
}
