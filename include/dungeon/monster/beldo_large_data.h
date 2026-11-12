#ifndef DUNGEON_MONSTER_BELDO_LARGE_DATA_H
#define DUNGEON_MONSTER_BELDO_LARGE_DATA_H

#include "common.h"

extern u8 encounter_recovery_flag;

/* The encounter callbacks read and write the first halfword at 0x801760D8. */
extern s16 encounter_blink_update_flag;

#endif
