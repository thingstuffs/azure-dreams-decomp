/* Relink of matched dungeon/func_80C18C5C; every changed retail word is a paired relocation. */
#define update_entity_movement_and_ground_height update_entity_action
#include "modules/dungeon_resource17_slot0.h"

void func_80161FF8(Resource17CallbackState *state, void *motion, void *position, void *actor)
{
    if (propagate_actor_action_flag(state, motion, position, actor) > 0) {
        state->callback = update_entity_action;
    }
}
