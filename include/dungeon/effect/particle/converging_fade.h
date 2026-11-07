#ifndef DUNGEON_EFFECT_PARTICLE_CONVERGING_FADE_H
#define DUNGEON_EFFECT_PARTICLE_CONVERGING_FADE_H

#include "common.h"
#include "shared/sprite_frame_state.h"

/* Body initialized by create_converging_fading_particle and read by its update callback. */
typedef struct ConvergingFadeBody {
    SpriteColor base_color;
    SpriteColor color;
    s32 draw_color;
    u8 pad_0C[0x8];
    s16 unk_14;
    u8 pad_16[0x1C];
    s16 fade_level;
    u8 pad_34[0xE];
    s16 target_x;
    s16 target_y;
    u16 target_z;
    u8 pad_48[0x4];
    s32 velocity_x;
    s32 velocity_y;
    s32 velocity_z;
    s32 acceleration_x;
    s32 acceleration_y;
    s32 acceleration_z;
} ConvergingFadeBody;

#endif
