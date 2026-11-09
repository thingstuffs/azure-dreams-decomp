#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/vector.h"
#include "engine/effect.h"
#include "sdk/libgte.h"
#include "slus.h"
#include "slus/data.h"

/* Advances staged object motion and marks completion. */
void update_staged_motion_effect(CdCueEffectBody *obj, ObjectPosition *position, SpriteFrameState *flags)
{
    s16 state;
    u16 prior_state;
    u16 *status_word;

    obj->timer = obj->timer + 1;
    advance_sprite_animation_and_textures(flags);
    state = obj->state;
    switch (state) {
    case 1:
        position->x.v = 0x01C00000 - (((rsin(obj->timer << 4) >> 4) * 3) << 14);
        position->y.v = ((rcos(obj->timer << 4) >> 4) << 13) + 0x900000;
        if (obj->timer < 0x40) {
            return;
        }
        position->x.v = 0x01000000;
        position->y.v = 0x900000;
        position->z.v = 0x700000;
        prior_state = obj->state;
        obj->timer = 0;
        obj->state = prior_state + 1;
        return;

    case 0:
    case 2:
        if (obj->completion == 0) {
            return;
        }
        prior_state = obj->state;
        obj->completion = 0;
        obj->timer = 0;
        obj->state = prior_state + 1;
        return;

    case 3:
        position->x.v = position->x.v + 0xFFF40000;
        position->y.v = position->y.v + 0x20000;
        if (obj->timer < 0x40) {
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
