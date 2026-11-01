#ifndef DUNGEON_OVL_1990800_H
#define DUNGEON_OVL_1990800_H
#include "modules/dungeon_native_abi.h"
#include "common.h"

/* Timer, origin, and local offset stored by follow_origin_and_fade_sprite. */
typedef struct OriginFollowingFadeSpriteBody {
    u8 pad_00[0x38];
    union { u16 u; s16 s; } ticks_remaining;
    s16 fade_divisor;
    u8 pad_3C[0x4];
    void *base_position;
    u16 offset_x;
    u16 offset_y;
    u16 offset_z;
} OriginFollowingFadeSpriteBody;

/* Bank flag: scalar declaration matches retail scheduling; following tail views remain external. */
extern s16 fading_quad_effect_updated;
void advance_effect_sequence(void *, void *, void *);
#endif
