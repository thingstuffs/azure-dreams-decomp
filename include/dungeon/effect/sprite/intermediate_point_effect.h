#ifndef DUNGEON_EFFECT_SPRITE_INTERMEDIATE_POINT_EFFECT_H
#define DUNGEON_EFFECT_SPRITE_INTERMEDIATE_POINT_EFFECT_H

#include "common.h"

/* Body of a point effect allocated by advance_target_chasing_emitter. */
typedef struct IntermediatePointEffectBody {
    void * owner;
    /* advance_target_chasing_emitter copies the origins at +4 and installs
     * update_randomized_intermediate_points. */
    struct {
        s16 x;
        s16 y;
        s16 z;
        u16 pad;
    } point_slots[5];
    s16 tex_u;
    s16 tex_v;
    s16 tex_width;
    s16 tex_height;
    u8 pad_34[0x4];
    s32 color;
    s16 phase;
    u16 anim_frame;
    s16 tpage;
    s16 clut;
} IntermediatePointEffectBody;

#endif
