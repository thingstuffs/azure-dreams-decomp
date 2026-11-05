#ifndef TOWN_PERSON_OFFSET_EFFECT_BODY_H
#define TOWN_PERSON_OFFSET_EFFECT_BODY_H

#include "common.h"

/* Both offset-effect creators install update_person_effect_fade for this node body. */
typedef struct PersonOffsetEffectBody {
    u8 pad_00[2];
    u16 ticks_left;
    s16 vertical_acceleration;
} PersonOffsetEffectBody;

#endif
