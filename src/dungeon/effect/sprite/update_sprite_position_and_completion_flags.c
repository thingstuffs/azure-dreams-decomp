#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"

extern void advance_sprite_animation_and_textures(void *);

/* Adjust the position, update the object, and propagate its status to state and global flags. */
void lower_sprite_until_animation_finishes(s16 *state, s32 *position, SpriteFrameState *object) {
    *(s32 *)((u8 *)position + 8) += 0xFFFE8000;
    advance_sprite_animation_and_textures(object);
    if (object->flags & 0x6000) {
        *(u16 *)((u8 *)state - 2) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
