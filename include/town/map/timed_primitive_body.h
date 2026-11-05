#ifndef TOWN_MAP_TIMED_PRIMITIVE_BODY_H
#define TOWN_MAP_TIMED_PRIMITIVE_BODY_H

#include "common.h"

/* Body initialized by create_randomized_position_effect and counted down by its callback. */
typedef struct TimedPrimitiveBody {
    u8 pad_00[2];
    u16 ticks_left;
} TimedPrimitiveBody;

#endif
