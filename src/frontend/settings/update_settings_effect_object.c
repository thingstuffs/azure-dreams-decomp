#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "frontend/settings.h"
/* Updates an object's movement, blinking, and removal flags from its animation state. */
void update_settings_effect_object(SettingsEffectObjectBody *object, ObjectPosition *motion, SpriteFrameState *sprite) {
    void *owner = object->owner;
    s16 state;

    if (*(u16 *)((char *)owner + 0x26) & 1)
        object->state = 255;
    state = object->state;
    switch (state) {
    case 0:
        break;
    case 1:
    {
        u16 ticks_left = object->ticks - 1;
        object->ticks = ticks_left;
        if ((s32)(ticks_left << 16) <= 0) {
            motion->x.v = motion->x.v + motion->velocity_x;
            motion->velocity_x = motion->velocity_x - 0x10000;
            if (motion->velocity_x == 0) {
                object->ticks = 4;
                object->state = 2;
            }
        }
    }
        break;
    case 2:
    {
        u16 ticks_left;
        motion->x.w.i = motion->x.unsigned_parts.integer +
            ((160 - motion->x.w.i) >> 1);
        ticks_left = object->ticks - 1;
        object->ticks = ticks_left;
        if ((s32)(ticks_left << 16) <= 0)
            object->state = 16;
    }
        break;
    case 16:
        motion->x.w.i = 160;
        if (*(s16 *)((char *)owner + 0x20) == 32) {
            if (*(s16 *)((char *)owner + 0x24) == object->index)
                object->state = 32;
            else {
                motion->velocity_x = 0xFFF80000;
                object->state = 33;
            }
        }
        break;
    case 32:
        if ((*(u16 *)((char *)owner + 0x22) >> 3) & 1)
            sprite->flags |= 0x80;
        else
            sprite->flags &= 0xFF7F;
        break;
    case 33:
    {
        s32 position = motion->x.v;
        if (position <= 0x1FFFFFF) {
            motion->x.v = position + motion->velocity_x;
            motion->velocity_x = motion->velocity_x + 0x20000;
        }
    }
        break;
    case 255:
    {
        s32 *flags_base = (s32 *)0x80080000;
        *(u16 *)((char *)object - 2) |= 0x8000;
        flags_base[0x14A0 / 4] |= 0x8000;
    }
        break;
    }
}
