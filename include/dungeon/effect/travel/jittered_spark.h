#ifndef DUNGEON_EFFECT_TRAVEL_JITTERED_SPARK_H
#define DUNGEON_EFFECT_TRAVEL_JITTERED_SPARK_H

#include "common.h"

/* Body allocated by create_spark_effect and advanced by update_spark_effect. */
typedef struct JitteredSparkEffectBody {
    u8 pad_00[0x1A];
    s16 heading;
    s16 remaining_steps;
    u8 pad_1E[0x8];
    s16 spawn_mode;
} JitteredSparkEffectBody;

#endif
