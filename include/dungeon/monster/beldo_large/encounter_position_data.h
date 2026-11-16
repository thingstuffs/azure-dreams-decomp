#ifndef DUNGEON_MONSTER_BELDO_LARGE_ENCOUNTER_POSITION_DATA_H
#define DUNGEON_MONSTER_BELDO_LARGE_ENCOUNTER_POSITION_DATA_H

#include "common.h"

/* Three coordinate words copied into the encounter objects' position records. */
typedef struct {
    s32 x;
    s32 y;
    s32 z;
} __attribute__((packed)) EncounterPositionVector;

extern EncounterPositionVector encounter_object_position_template;

#endif
