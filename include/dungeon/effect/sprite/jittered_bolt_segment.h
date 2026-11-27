#ifndef DUNGEON_EFFECT_SPRITE_JITTERED_BOLT_SEGMENT_H
#define DUNGEON_EFFECT_SPRITE_JITTERED_BOLT_SEGMENT_H

#include "common.h"

/* One jittered bolt segment created by the attack sequence controller. */
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
    s16 tex_u;
    s16 tex_v;
    u16 tex_width;
    u16 tex_height;
    void *target;
    u32 color;
    s16 phase;
    u16 anim_frame;
    u16 tpage;
    u16 clut;
} JitteredBoltSegmentBody;

#endif
