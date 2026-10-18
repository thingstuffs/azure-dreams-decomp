/* Relink of matched dungeon/func_80C18C5C; every changed retail word is a paired relocation. */
#define update_entity_movement_and_ground_height func_80164E68
#include "modules/dungeon_resource17_slot0.h"

void func_80168154(Resource17CallbackState *state, void *motion, void *position, void *actor)
{
    if (propagate_actor_action_flag(state, motion, position, actor) > 0) {
        state->callback = func_80164E68;
    }
}
