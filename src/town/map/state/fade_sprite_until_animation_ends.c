#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "slus.h"
#include "town/map/state.h"
#include "shared/object_node.h"

/*
 * Advances sprite animation and reduces the packed color by adding 0xFFEFEFF0, then flags removal
 * when animation flags 0x6000 are set.
 */
void fade_sprite_until_animation_ends(void *flags_end, ObjectPosition *unused, SpriteFrameState *state) {
    advance_sprite_animation_and_textures(state);
    state->color.word += 0xFFEFEFF0;
    if (state->flags & 0x6000) {
        NODE_HEADER(flags_end)->flags |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
