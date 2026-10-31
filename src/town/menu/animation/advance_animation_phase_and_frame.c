#include "common.h"
#include "town/menu/motion.h"
#include "shared/entity.h"

typedef struct S_800A3918_1 {
    u8 pad_00[0x74];
    void * unk_74;
} S_800A3918_1;   /* D_8008274C in advance_animation_phase_and_frame */


extern void *D_8008274C;
extern s32 D_800C5100;
extern union { s16 s; u16 u; } town_display_offset;

/* Advances the animation phase and frame index, applying the state-one offset transition. */
void advance_animation_phase_and_frame(MenuAnimationPhaseObject *anim, ObjectPosition *unused) {
    s32 phase;
    s16 offset;
    u16 offset_bits;

    offset = anim->transition;
    switch (offset) {
    case 0:
        if (anim->state == 0) {
            phase = (s16)(anim->offset.s + 0x1BC0);
            anim->phase += 2;
            phase %= 0x1C00;
            anim->offset.u = phase;
        } else {
            phase = (s16)(anim->offset.s + 0x1B71);
            anim->phase += 1;
            phase %= 0x1C00;
            anim->offset.u = phase;
        }
        anim->frame++;
        if (((S_800A3918_1 *)D_8008274C)->unk_74 == &D_800C5100) {
            anim->transition = 1;
        }
        break;
    case 1:
        offset = town_display_offset.s;
        offset_bits = town_display_offset.u;
        if (offset < -0x1FFF) {
            town_display_offset.s = -0x2000;
        } else {
            anim->step -= 0x20;
            offset = offset_bits + anim->step;
            town_display_offset.s = offset;
            if (offset < -0x1FFF) {
                town_display_offset.s = -0x2000;
            }
        }
        if (anim->target.s < 0x200) {
            anim->target.s = anim->target.u + 0x20;
        }
        if (anim->state == 0) {
            phase = (s16)(anim->offset.s + 0x1C00 - anim->target.u);
            anim->phase += 2;
            phase %= 0x1C00;
            anim->offset.u = phase;
        } else {
            phase = (s16)(anim->offset.s + 0x1C00 - anim->target.s * 2);
            anim->phase += 1;
            phase %= 0x1C00;
            anim->offset.u = phase;
        }
        anim->frame++;
        break;
    }

finish:
    anim->value = anim->offset.u / 0x200 + 0x10;
}
