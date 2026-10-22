#include "common.h"
#include "shared/object_flags.h"

extern void advance_sprite_animation_and_textures(void *object);
extern void select_sprite_entry(void *object, s32 kind, s32 value);

/* Advances the animation, moves its sprite, and marks completion after eight ticks. */
void advance_eight_tick_animation(u16 *anim, u32 *motion, u16 *sprite) {
    s32 frame_bits;
    s32 frame_index;
    s32 div_index;

    frame_bits = anim[0] + 1;
    anim[0] = frame_bits;
    frame_bits = frame_bits << 16;
    frame_index = frame_bits >> 16;
    if (frame_index >= 8) {
        anim[-1] |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    }
    if (frame_index >= 6) {
        s32 frame_offset;
        frame_offset = frame_index + 6;
        frame_index = ((s16 *)anim)[2] + frame_offset;
        div_index = frame_index;
        sprite[9] = anim[3] + (frame_index % 8) + 8;
    } else {
        s32 frame_offset;
        frame_offset = frame_index + 6;
        frame_index = ((s16 *)anim)[2] + frame_offset;
        div_index = frame_index;
        sprite[9] = anim[3] + (frame_index % 8);
        motion[0] += motion[3];
        motion[1] += motion[4];
    }
    advance_sprite_animation_and_textures(sprite);
    if (sprite[10] & 0x6000) {
        select_sprite_entry(sprite, 0x30, 0);
    }
}
