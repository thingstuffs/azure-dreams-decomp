#ifndef DUNGEON_EFFECT_SPRITE_JITTERED_TRAIL_SEGMENT_H
#define DUNGEON_EFFECT_SPRITE_JITTERED_TRAIL_SEGMENT_H

#include "common.h"

/* Body of a trail segment created by the jittered point sequence. */
typedef struct JitteredBoltSegmentBody {
    void *owner;
    u16 unk_04;
    u16 unk_06;
    u16 unk_08;
    u8 pad_0A[0x1A];
    u16 unk_24;
    u16 unk_26;
    s16 unk_28;
    u8 pad_2A[0x2];
    s16 unk_2C;
    s16 unk_2E;
    u8 pad_30[0x4];
    void *unk_34;
    u8 pad_38[0x4];
    s16 unk_3C;
    u16 unk_3E;
} JitteredBoltSegmentBody;

#endif
