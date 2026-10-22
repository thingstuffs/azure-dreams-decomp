#include "common.h"
#include "shared/object_flags.h"

extern void advance_sprite_animation_and_textures(void *arg);

// Updates the object, retains its 0x6000 flags, and marks the preceding and global flags if any remain.
void update_effect_and_retain_flags(void *dataAfterFlags, void *unused, void *object) {
    u16 retainedFlags;

    advance_sprite_animation_and_textures(object);
    retainedFlags = *(u16 *)((u8 *)object + 0x14) & 0x6000;
    *(u16 *)((u8 *)object + 0x14) = retainedFlags;
    if (retainedFlags != 0) {
        *(u16 *)((u8 *)dataAfterFlags - 2) |= NODE_REMOVE;
        object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
    }
}
