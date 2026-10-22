#ifndef DUNGEON_MONSTER_CYCLONE_H
#define DUNGEON_MONSTER_CYCLONE_H

#include "common.h"

/* Monster-owned imports; preserve their registered declaration contracts. */
extern u8 cyclone_direction_frames[];

void advance_cyclone_frame_effect(u16 *anim_state, u32 *motion, u16 *sprite);

#endif
