#ifndef DUNGEON_MONSTER_MANOEVA_OFFSET_MOTION_OBJECT_H
#define DUNGEON_MONSTER_MANOEVA_OFFSET_MOTION_OBJECT_H

#include "common.h"

/* Body allocated by spawn_offset_motion_object and advanced by its update callback. */
typedef struct OffsetMotionObjectBody {
    s16 *facing_source;
    u8 pad_04[0x1C];
    u16 remaining_ticks;
} OffsetMotionObjectBody;

#endif
