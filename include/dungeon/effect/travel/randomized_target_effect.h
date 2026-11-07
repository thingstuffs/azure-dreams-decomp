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
    u16 phase;
    s16 elapsed_ticks;
    s16 delay_ticks; /* elapsed ticks required before the travel phase */
    s16 quarter_turn_ticks;
} RandomizedTargetEffectBody;

#endif
