#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"

extern void advance_sprite_animation_and_textures(void *source);

// Process the source and set destination and global flags when source status bits are set.
void find_first_entry_matching_keys(void *destination, s32 unused, SpriteFrameState *source)
{
    advance_sprite_animation_and_textures(source);
    if (source->flags & 0x6000) {
        *(u16 *)((u8 *)destination - 2) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
