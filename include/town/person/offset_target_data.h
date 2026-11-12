#ifndef TOWN_PERSON_OFFSET_TARGET_DATA_H
#define TOWN_PERSON_OFFSET_TARGET_DATA_H

#include "common.h"

/* Both offset-motion readers use the coordinate pointer at owner +0x08. */
typedef struct TownOffsetTargetCoords {
    s16 pad0;
    s16 x;
    s16 pad4;
    s16 y;
} TownOffsetTargetCoords;

typedef struct TownOffsetTargetOwner {
    u8 pad0[8];
    TownOffsetTargetCoords *coords;
} TownOffsetTargetOwner;

extern TownOffsetTargetOwner *person_offset_target_owner;

#endif
