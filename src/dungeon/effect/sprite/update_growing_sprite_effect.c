#include "common.h"
#include "shared/object_flags.h"

extern s32 advance_sprite_animation_and_textures();

/* Increment the object counter, advance paired state values, and propagate status flags. */
void update_growing_sprite_effect(void *object_ref, void *unused, void *state) {
    void *object;
    u16 next_value;

    object = *(void **)object_ref;
    *(u16 *)((u8 *)object + 0x14) =
        (u16)(*(u16 *)((u8 *)object + 0x14) + 1);
    next_value = *(u16 *)((u8 *)state + 0x1E) + 0x800;
    *(u16 *)((u8 *)state + 0x1E) = next_value;
    *(u16 *)((u8 *)state + 0x1C) = next_value;
    advance_sprite_animation_and_textures(state);
    if (*(u16 *)((u8 *)state + 0x14) & 0x6000) {
        *(u16 *)((u8 *)object_ref - 2) =
            (u16)(*(u16 *)((u8 *)object_ref - 2) | NODE_REMOVE);
        object_flag_block.flags = (s32)(object_flag_block.flags | OBJECT_REMOVE_PENDING);
    }
}
