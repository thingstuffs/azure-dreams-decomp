#include "modules/dungeon_resource17_slot0.h"

void func_801743B4(Resource17CallbackState *state, void *motion, void *position, void *actor)
{
    if (update_spinning_actor_fall(state, motion, position, actor)) {
        state->callback = update_entity_movement_and_ground_height;
    }
}
