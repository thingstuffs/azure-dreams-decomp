#ifndef SHARED_FADE_EFFECT_H
#define SHARED_FADE_EFFECT_H

#include "common.h"
#include "shared/sprite_frame_state.h"

/* Body shared by damped fade callbacks and their effect creators. */
typedef struct FadeEffect {
    SpriteColor base_color; /* packed at creation, read as RGB by fade callbacks */
    union { struct { u8 red, green, blue, pad; } color; s32 packed; } current;
    s32 output;
    u8 pad0c[0x8];
    u16 seed_angle; /* set by spawn_randomized_directional_effect */
    u8 pad16[0x1c];
    s16 remaining, total;
} FadeEffect;

#endif
