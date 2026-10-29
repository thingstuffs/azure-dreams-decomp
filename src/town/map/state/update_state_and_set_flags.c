#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "slus.h"
#include "town/map/state.h"

/*
 * Advances sprite animation and reduces the packed color by adding 0xFFEFEFF0, then flags removal
 * when animation flags 0x6000 are set.
 */
void update_state_and_set_flags(void *flags_end, void *unused, SpriteFrameState *state) {
    advance_sprite_animation_and_textures(state);
    state->color.word += 0xFFEFEFF0;
    if (state->flags & 0x6000) {
        *(u16 *)((s8 *)flags_end - 2) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
