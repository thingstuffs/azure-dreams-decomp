#include "common.h"
#include "shared/sprite_frame_state.h"
#include "engine/graphics.h"
#include "engine/sprite.h"

/* Struct with a 16-bit flags field at offset 0x14, matching the sibling
 * func_80048374's Struct_80048374 layout. */

/* Updates the entity, then dispatches and clears bit 0x20 if any flags in 0x1220 are set. */
void step_actor_animation(SpriteFrameState *entity, void *slot_index)
{
    advance_actor_step_sequence(entity);
    if (entity->flags & 0x1220) {
        register_sprite_slot(entity, slot_index);
        entity->flags &= 0xFFDF;
    }
}
