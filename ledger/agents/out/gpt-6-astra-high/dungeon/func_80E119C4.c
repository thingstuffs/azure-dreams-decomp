#include "common.h"

extern u32 D_800814A0[3];
extern void func_800478B8(void *arg0);
extern void func_80047784(void *arg0, s32 arg1, s32 arg2);

/* Advances the animation, moves its sprite, and marks completion after eight ticks. */
void func_801751C4(u16 *anim, u32 *motion, u16 *sprite) {
    s32 frame_bits;
    s32 frame_index;
    s32 div_index;

    frame_bits = anim[0] + 1;
    anim[0] = frame_bits;
    frame_bits = frame_bits << 16;
    frame_index = frame_bits >> 16;
    if (frame_index >= 8) {
        anim[-1] |= 0x8000;
        D_800814A0[0] |= 0x8000;
        return;
    }
    if (frame_index >= 6) {
        s32 frame_offset;
        frame_offset = frame_index + 6;
        frame_index = ((s16 *)anim)[2] + frame_offset;
        div_index = frame_index;
        if (frame_index < 0) {
            div_index = frame_index + 7;
        }
        sprite[9] = anim[3] + (frame_index - ((div_index >> 3) << 3)) + 8;
    } else {
        s32 frame_offset;
        frame_offset = frame_index + 6;
        frame_index = ((s16 *)anim)[2] + frame_offset;
        div_index = frame_index;
        if (frame_index < 0) {
            div_index = frame_index + 7;
        }
        sprite[9] = anim[3] + (frame_index - ((div_index >> 3) << 3));
        motion[0] += motion[3];
        motion[1] += motion[4];
    }
    func_800478B8(sprite);
    if (sprite[10] & 0x6000) {
        func_80047784(sprite, 0x30, 0);
    }
}
