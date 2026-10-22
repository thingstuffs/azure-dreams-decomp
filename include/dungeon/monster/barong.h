#ifndef DUNGEON_MONSTER_BARONG_H
#define DUNGEON_MONSTER_BARONG_H

#include "common.h"
#include "shared/sprite_frame_state.h"

/* Monster-owned imports; preserve their registered declaration contracts. */
extern u8 barong_direction_frames[];

void advance_arcing_actor_move(void *action, void *motion, SpriteFrameState *sprite, void *actor);
#endif
