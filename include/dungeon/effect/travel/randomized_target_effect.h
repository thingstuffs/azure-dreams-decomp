#ifndef DUNGEON_EFFECT_TRAVEL_RANDOMIZED_TARGET_EFFECT_H
#define DUNGEON_EFFECT_TRAVEL_RANDOMIZED_TARGET_EFFECT_H

#include "common.h"

/* State shared by the randomized-target creator and its rotating/fading callback. */
typedef struct RandomizedTargetEffectBody {
    void *owner;
    s32 start_x;
    s32 start_y;
    s32 start_z;
    u8 pad_10[0xC];
    s32 target_x;
    s32 target_y;
    s32 target_z;
    s32 offset_x;
    s32 offset_y;
    s32 offset_z;
    union { s16 s; u16 u; } phase;
    union { s16 s; u16 u; } elapsed_ticks;
    u8 pad_38[0x2];
    union { s16 s; u16 u; } quarter_turn_ticks;
} RandomizedTargetEffectBody;

#endif
