#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"

extern int advance_sprite_animation_and_textures(void *arg);

/* Updates state and sets local and global flags when either status bit is set. */
void update_state_and_set_flags(void *flags_end, void *unused, SpriteFrameState *state) {
    advance_sprite_animation_and_textures(state);
    state->color.word += 0xFFEFEFF0;
    if (state->flags & 0x6000) {
        *(u16 *)((s8 *)flags_end - 2) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
