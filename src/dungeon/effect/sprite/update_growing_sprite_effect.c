#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "slus.h"


/* Increment the object counter, advance paired state values, and propagate status flags. */
void update_growing_sprite_effect(void *object_ref, void *unused, SpriteFrameState *state) {
    void *object;
    u16 next_value;

    object = *(void **)object_ref;
    *(u16 *)((u8 *)object + 0x14) =
        (u16)(*(u16 *)((u8 *)object + 0x14) + 1);
    next_value = state->scale_y + 0x800;
    state->scale_y = next_value;
    state->scale_x = next_value;
    advance_sprite_animation_and_textures(state);
    if (state->flags & 0x6000) {
        *(u16 *)((u8 *)object_ref - 2) =
            (u16)(*(u16 *)((u8 *)object_ref - 2) | NODE_REMOVE);
        object_flag_block.flags = (s32)(object_flag_block.flags | OBJECT_REMOVE_PENDING);
    }
}
