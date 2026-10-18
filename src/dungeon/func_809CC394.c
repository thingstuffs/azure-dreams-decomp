#include "modules/dungeon_resource03_slot0.h"

void fade_entity_colors_to_neutral(Resource03CallbackState *state, void *motion, void *position, void *actor)
{
    if (update_spinning_actor_fall(state, motion, position, actor)) {
        state->callback = func_80170E54;
    }
}
