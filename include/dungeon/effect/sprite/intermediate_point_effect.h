#ifndef DUNGEON_EFFECT_SPRITE_INTERMEDIATE_POINT_EFFECT_H
#define DUNGEON_EFFECT_SPRITE_INTERMEDIATE_POINT_EFFECT_H

#include "common.h"

/* Body of a point effect allocated by advance_target_chasing_emitter. */
typedef struct IntermediatePointEffectBody {
    void * unk_00;
    /* advance_target_chasing_emitter copies the origins at +4 and installs
     * update_randomized_intermediate_points. */
    struct {
        s16 x;
        s16 y;
        s16 z;
        u16 pad;
    } point_slots[5];
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
