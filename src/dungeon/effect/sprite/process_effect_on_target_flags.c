#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"

extern void advance_sprite_animation_and_textures(void *target);

/* Marks the record when target flags are set, then processes the target. */
void process_effect_on_target_flags(u16 *record, void *unused, SpriteFrameState *target) {
    if (target->flags & 0x6000) {
        u16 *record_flags = (u16 *)((u8 *)record - 2);
        *record_flags = (u16)(*record_flags | 0x8000);
        object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
    }
    advance_sprite_animation_and_textures(target);
}
