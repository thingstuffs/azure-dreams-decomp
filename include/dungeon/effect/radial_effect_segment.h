#ifndef DUNGEON_EFFECT_RADIAL_EFFECT_SEGMENT_H
#define DUNGEON_EFFECT_RADIAL_EFFECT_SEGMENT_H

#include "common.h"

/* Body of a segment allocated by create_radial_effect_segments. */
typedef struct RadialEffectSegmentBody {
    u8 pad_00[0xC];
    s16 ticks_remaining;
    s16 total_ticks;
    s16 segment_index;
    u8 pad_12[0x2];
    void *unk_14;
    u8 pad_18[0x2C];
    s16 x[4];
    s16 y[4];
    s16 unk_54;
    s16 unk_56;
    s16 unk_58;
    s16 unk_5A;
} RadialEffectSegmentBody;

#endif
