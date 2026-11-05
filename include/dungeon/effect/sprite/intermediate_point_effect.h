#ifndef DUNGEON_EFFECT_SPRITE_INTERMEDIATE_POINT_EFFECT_H
#define DUNGEON_EFFECT_SPRITE_INTERMEDIATE_POINT_EFFECT_H

#include "common.h"

/* Body of a point effect allocated by advance_target_chasing_emitter. */
typedef struct IntermediatePointEffectBody {
    void * unk_00;
    /* UNION: update_randomized_intermediate_points reads slot 0 coordinates as
     * signed deltas and unsigned origins; advance_target_chasing_emitter allocates
     * this body, copies the origins at +4, and installs that updater. */
    struct {
        union { s16 s; u16 u; } x;
        union { s16 s; u16 u; } y;
        union { s16 s; u16 u; } z;
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
