#ifndef DUNGEON_MONSTER_CYCLONE_BOBBING_MOTION_H
#define DUNGEON_MONSTER_CYCLONE_BOBBING_MOTION_H

#include "common.h"
#include "shared/entity.h"

/* Three Cyclone creators copy a path into this body and install the bobbing updater. */
typedef struct CycloneBobbingMotionBody {
    s16 state;
    u16 count;
    ObjectPosition path;
} CycloneBobbingMotionBody;

#endif
