#ifndef DUNGEON_MONSTER_CYCLONE_BOBBING_MOTION_H
#define DUNGEON_MONSTER_CYCLONE_BOBBING_MOTION_H

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

/* Three Cyclone creators copy a path into this body and install the bobbing updater. */
typedef struct CycloneBobbingMotionBody {
    s16 state;
    u16 count;
    ObjectPosition path;
} CycloneBobbingMotionBody;

void advance_cyclone_bobbing_effect(CycloneBobbingMotionBody *motion, ObjectPosition *position, SpriteFrameState *output);

#endif
