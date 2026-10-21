#include "common.h"
#include "shared/object_flags.h"

extern int advance_sprite_animation_and_textures(void *arg);

/* Updates state and sets local and global flags when either status bit is set. */
void update_state_and_set_flags(void *flags_end, void *unused, void *state) {
    advance_sprite_animation_and_textures(state);
    *(s32 *)((s8 *)state + 0xC) += 0xFFEFEFF0;
    if (*(u16 *)((s8 *)state + 0x14) & 0x6000) {
        *(u16 *)((s8 *)flags_end - 2) |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }
}
