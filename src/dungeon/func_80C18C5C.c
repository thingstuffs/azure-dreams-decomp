#include "modules/dungeon_resource17_slot0.h"

void func_8017445C(Resource17CallbackState *state, void *motion, void *position, void *actor)
{
    if (propagate_actor_action_flag(state, motion, position, actor) > 0) {
        state->callback = update_entity_movement_and_ground_height;
    }
}
