#include "common.h"
#include "engine/graphics.h"
#include "engine/sprite.h"

/* Struct with a 16-bit flags field at offset 0x14, matching the sibling
 * func_80048374's Struct_80048374 layout. */
typedef struct {
    u8 pad[0x14];
    u16 unk14;
} S_80048AC8;

/* Updates the entity, then dispatches and clears bit 0x20 if any flags in 0x1220 are set. */
void step_actor_animation(S_80048AC8 *entity, void *slot_index)
{
    advance_actor_step_sequence(entity);
    if (entity->unk14 & 0x1220) {
        register_sprite_slot(entity, slot_index);
        entity->unk14 &= 0xFFDF;
    }
}
