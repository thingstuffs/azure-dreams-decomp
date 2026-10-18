#include "modules/dungeon_resource17_slot0.h"

void blend_animation_palette_and_complete(Resource17CallbackState *state, void *motion, void *position, void *actor)
{
    if (resolve_actor_floor_trap_once(state, motion, position, actor) > 0) {
        state->callback = update_entity_movement_and_ground_height;
    }
}
