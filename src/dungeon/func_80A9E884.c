#include "modules/dungeon_resource08_slot0.h"

void create_four_directional_effects(Resource08CallbackState *state, void *motion, void *position, void *actor)
{
    if (update_spinning_actor_fall(state, motion, position, actor)) {
        state->callback = update_actor_behavior_and_effect;
    }
}
