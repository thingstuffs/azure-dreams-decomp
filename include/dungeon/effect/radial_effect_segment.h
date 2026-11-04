#ifndef DUNGEON_EFFECT_RADIAL_EFFECT_SEGMENT_H
#define DUNGEON_EFFECT_RADIAL_EFFECT_SEGMENT_H

#include "common.h"

/* Body of a segment allocated by create_radial_effect_segments. */
typedef struct RadialEffectSegmentBody {
    u8 pad_00[0xC];
    s16 unk_0C;
    s16 unk_0E;
    s16 unk_10;
    u8 pad_12[0x2];
    void *unk_14;
    u8 pad_18[0x2C];
    s16 unk_44;
    s16 unk_46;
    s16 unk_48;
    s16 unk_4A;
    s16 unk_4C;
    s16 unk_4E;
    s16 unk_50;
    s16 unk_52;
    s16 unk_54;
    s16 unk_56;
    s16 unk_58;
    s16 unk_5A;
} RadialEffectSegmentBody;

#endif
