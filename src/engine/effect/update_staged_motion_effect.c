#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/vector.h"
#include "engine/effect.h"
#include "sdk/libgte.h"
#include "slus.h"
#include "slus/data.h"

/* Advances staged object motion and marks completion. */
void update_staged_motion_effect(CdCueEffectBody *obj, IntVector3 *position, SpriteFrameState *flags)
{
    s16 state;
    u16 prior_state;
    u16 *status_word;

    obj->timer.u = obj->timer.u + 1;
    advance_sprite_animation_and_textures(flags);
    state = obj->state.s;
    switch (state) {
    case 1:
        position->x = 0x01C00000 - (((rsin(((s16) obj->timer.u) << 4) >> 4) * 3) << 14);
        position->y = ((rcos(((s16) obj->timer.u) << 4) >> 4) << 13) + 0x900000;
        if (((s16) obj->timer.u) < 0x40) {
            return;
        }
        position->x = 0x01000000;
        position->y = 0x900000;
        position->z = 0x700000;
        prior_state = obj->state.u;
        obj->timer.u = 0;
        obj->state.s = prior_state + 1;
        return;

    case 0:
    case 2:
        if (obj->completion == 0) {
            return;
        }
        prior_state = obj->state.u;
        obj->completion = 0;
        obj->timer.u = 0;
        obj->state.s = prior_state + 1;
        return;

    case 3:
        position->x = position->x + 0xFFF40000;
        position->y = position->y + 0x20000;
        if (((s16) obj->timer.u) < 0x40) {
            return;
        }
        break;

    default:
        flags->color.c.b = 0;
        flags->color.c.g = 0;
        flags->color.c.r = 0;
        break;
    }
    obj->owner.motion->status = 0;
    obj->owner.motion->count = obj->owner.motion->count + 1;
    status_word = (u16 *) obj - 1;
    *status_word |= 0x8000;
    D_800814A0_abs |= 0x8000;
}
