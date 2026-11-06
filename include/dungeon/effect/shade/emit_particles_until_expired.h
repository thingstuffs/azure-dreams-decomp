#ifndef DUNGEON_EFFECT_SHADE_EMIT_PARTICLES_UNTIL_EXPIRED_H
#define DUNGEON_EFFECT_SHADE_EMIT_PARTICLES_UNTIL_EXPIRED_H

#include "common.h"
#include "shared/sprite_frame_state.h"

/* Color and lifetime state shared by the two timed particle emitters. */
struct Rec_func_800D4BD4_arg1;
typedef struct FadingMotionParticleBody {
    u8 pad_00[0xC];
    SpriteColor color;
    u8 pad_10[0xE];
    s16 remaining_ticks;
    s16 initial_ticks;
    u8 pad_22[0x2];
    struct Rec_func_800D4BD4_arg1 *source_emitter;
} FadingMotionParticleBody;

#endif
