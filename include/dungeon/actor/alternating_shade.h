#ifndef DUNGEON_ACTOR_ALTERNATING_SHADE_H
#define DUNGEON_ACTOR_ALTERNATING_SHADE_H

#include "common.h"

/* Created by create_visual_object and advanced through its installed shade callback. */
typedef struct AlternatingShadeBody {
    u8 pad_00[0x66];
    u16 ticks_left;
    u16 frame;
    u16 intensity;
} AlternatingShadeBody;

#endif
