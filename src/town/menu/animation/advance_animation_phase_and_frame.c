#include "common.h"
#include "town/menu/motion.h"
#include "shared/entity.h"
#include "shared/town_object.h"
#include "town/menu/animation.h"
#include "town/map/display_offset_data.h"



extern void *D_8008274C;
extern s32 D_800C5100;

/* Advances the animation phase and frame index, applying the state-one offset transition. */
void advance_animation_phase_and_frame(MenuAnimationPhaseObject *anim, ObjectPosition *unused) {
    s32 phase;
    s16 offset;
    u16 offset_bits;

    offset = anim->transition;
    switch (offset) {
    case 0:
        if (anim->state == 0) {
            phase = (s16)(anim->offset + 0x1BC0);
            anim->phase += 2;
            phase %= 0x1C00;
            anim->offset = phase;
        } else {
            phase = (s16)(anim->offset + 0x1B71);
            anim->phase += 1;
            phase %= 0x1C00;
            anim->offset = phase;
        }
        anim->frame++;
        if (((TownObjectRecord *)D_8008274C)->unk_74.as_pv == &D_800C5100) {
            anim->transition = 1;
        }
        break;
    case 1:
        offset = (s16)town_display_offset;
        offset_bits = (u16)town_display_offset;
        if (offset < -0x1FFF) {
            town_display_offset = -0x2000;
        } else {
            anim->step -= 0x20;
            offset = offset_bits + anim->step;
            town_display_offset = offset;
            if (offset < -0x1FFF) {
                town_display_offset = -0x2000;
            }
        }
        if (anim->target < 0x200) {
            anim->target = (u16)anim->target + 0x20;
        }
        if (anim->state == 0) {
            phase = (s16)(anim->offset + 0x1C00 - (u16)anim->target);
            anim->phase += 2;
            phase %= 0x1C00;
            anim->offset = phase;
        } else {
            phase = (s16)(anim->offset + 0x1C00 - anim->target * 2);
            anim->phase += 1;
            phase %= 0x1C00;
            anim->offset = phase;
        }
        anim->frame++;
        break;
    }

finish:
    anim->value = (s16)anim->offset / 0x200 + 0x10;
}
