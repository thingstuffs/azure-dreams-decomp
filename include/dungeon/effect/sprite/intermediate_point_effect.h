#ifndef DUNGEON_EFFECT_SPRITE_INTERMEDIATE_POINT_EFFECT_H
#define DUNGEON_EFFECT_SPRITE_INTERMEDIATE_POINT_EFFECT_H

#include "common.h"

/* Body of a point effect allocated by advance_target_chasing_emitter. */
typedef struct IntermediatePointEffectBody {
    void * unk_00;
    union { s16 s; u16 u; } unk_04;   /* accessed as both */
    union { s16 s; u16 u; } unk_06;   /* accessed as both */
    union { s16 s; u16 u; } unk_08;   /* accessed as both */
    u8 pad_0A[0x1A];
    union { s16 s; u16 u; } unk_24;
    union { s16 s; u16 u; } unk_26;
    union { s16 s; u16 u; } unk_28;
    u8 pad_2A[0x2];
    s16 unk_2C;
    s16 unk_2E;
    s16 unk_30;
    s16 unk_32;
    u8 pad_34[0x4];
    s32 unk_38;
    union { s16 s; u16 u; } unk_3C;   /* accessed as both */
    union { s16 s; u16 u; } unk_3E;
    s16 unk_40;
    s16 unk_42;
} IntermediatePointEffectBody;

#endif
