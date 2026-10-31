#ifndef DUNGEON_EFFECT_MOTION_VARIANT_EFFECT_WITH_RANDOM_MOTION_H
#define DUNGEON_EFFECT_MOTION_VARIANT_EFFECT_WITH_RANDOM_MOTION_H

#include "common.h"
#include "shared/sprite_source.h"

/* Motion, fade, sprite source, and lifetime state for randomized variants. */
typedef struct VariantEffectWithRandomMotionBody {
    u8 pad_00[0x8];
    SpriteSourceEntry *sprite_entries;
    u8 pad_0C[0x4];
    union { s16 s; u16 u; } lifetime;
    s16 fade_color;
    union { s16 s; u16 u; } angle_x_step;
    union { s16 s; u16 u; } angle_y_step;
} VariantEffectWithRandomMotionBody;

#endif
