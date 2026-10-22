#include "common.h"
#include "shared/object_flags.h"

extern void advance_sprite_animation_and_textures(void *object);
extern void select_sprite_entry(void *object, s32 kind, s32 value);

/* Advances animation and motion, updates the sprite frame, and marks completion at step eight. */
/* Animates an eight-step effect, moves it during the first five steps, switches palette rows, and removes
 * it at step eight. */
void func_80175480(u16 *anim_state, u32 *motion, u16 *sprite) {
    s32 step_bits;
    s32 frame;
    s32 rounded_frame;

    step_bits = anim_state[0] + 1;
    anim_state[0] = step_bits;
    step_bits = step_bits << 16;
    frame = step_bits >> 16;
    if (frame >= 8) {
        anim_state[-1] |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    }
    if (frame >= 6) {
        s32 frame_offset;
        frame_offset = frame + 6;
        frame = ((s16 *)anim_state)[2] + frame_offset;
        rounded_frame = frame;
        sprite[9] = anim_state[3] + (frame % 8) + 8;
    } else {
        s32 frame_offset;
        frame_offset = frame + 6;
        frame = ((s16 *)anim_state)[2] + frame_offset;
        rounded_frame = frame;
        sprite[9] = anim_state[3] + (frame % 8);
        motion[0] += motion[3];
        motion[1] += motion[4];
    }
    advance_sprite_animation_and_textures(sprite);
    if (sprite[10] & 0x6000) {
        select_sprite_entry(sprite, 0x31, 0);
    }
}
