#include "common.h"

extern u32 D_800814A0[3];
extern void func_800478B8(void *arg0);
extern void func_80047784(void *arg0, s32 arg1, s32 arg2);

/* Advances animation and motion, updates the sprite frame, and marks completion at step eight. */
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
        D_800814A0[0] |= 0x8000;
        return;
    }
    if (frame >= 6) {
        s32 frame_offset;
        frame_offset = frame + 6;
        frame = ((s16 *)anim_state)[2] + frame_offset;
        rounded_frame = frame;
        if (frame < 0) {
            rounded_frame = frame + 7;
        }
        sprite[9] = anim_state[3] + (frame - ((rounded_frame >> 3) << 3)) + 8;
    } else {
        s32 frame_offset;
        frame_offset = frame + 6;
        frame = ((s16 *)anim_state)[2] + frame_offset;
        rounded_frame = frame;
        if (frame < 0) {
            rounded_frame = frame + 7;
        }
        sprite[9] = anim_state[3] + (frame - ((rounded_frame >> 3) << 3));
        motion[0] += motion[3];
        motion[1] += motion[4];
    }
    func_800478B8(sprite);
    if (sprite[10] & 0x6000) {
        func_80047784(sprite, 0x31, 0);
    }
}
