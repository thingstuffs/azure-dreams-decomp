#include "modules/dungeon_resource17_slot0.h"

void func_801738A8(Resource17CallbackState *state, void *motion, void *position, void *actor)
{
    if (update_actor_hop_and_grow(state, motion, position, actor)) {
        state->callback = update_entity_movement_and_ground_height;
    }
}
