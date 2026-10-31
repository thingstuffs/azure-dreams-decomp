#include "common.h"
#include "frontend/settings.h"
/* Updates an object's movement, blinking, and removal flags from its animation state. */
void update_settings_effect_object(SettingsEffectObjectBody *object, void *motion, void *sprite) {
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
            *(s32 *)motion = *(s32 *)motion + *(s32 *)((char *)motion + 0xC);
            *(s32 *)((char *)motion + 0xC) = *(s32 *)((char *)motion + 0xC) - 0x10000;
            if (*(s32 *)((char *)motion + 0xC) == 0) {
                object->ticks = 4;
                object->state = 2;
            }
        }
    }
        break;
    case 2:
    {
        u16 ticks_left;
        *(s16 *)((char *)motion + 2) = *(u16 *)((char *)motion + 2) +
            ((160 - *(s16 *)((char *)motion + 2)) >> 1);
        ticks_left = object->ticks - 1;
        object->ticks = ticks_left;
        if ((s32)(ticks_left << 16) <= 0)
            object->state = 16;
    }
        break;
    case 16:
        *(s16 *)((char *)motion + 2) = 160;
        if (*(s16 *)((char *)owner + 0x20) == 32) {
            if (*(s16 *)((char *)owner + 0x24) == object->index)
                object->state = 32;
            else {
                *(s32 *)((char *)motion + 0xC) = 0xFFF80000;
                object->state = 33;
            }
        }
        break;
    case 32:
        if ((*(u16 *)((char *)owner + 0x22) >> 3) & 1)
            *(u16 *)((char *)sprite + 0x14) |= 0x80;
        else
            *(u16 *)((char *)sprite + 0x14) &= 0xFF7F;
        break;
    case 33:
    {
        s32 position = *(s32 *)motion;
        if (position <= 0x1FFFFFF) {
            *(s32 *)motion = position + *(s32 *)((char *)motion + 0xC);
            *(s32 *)((char *)motion + 0xC) = *(s32 *)((char *)motion + 0xC) + 0x20000;
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
