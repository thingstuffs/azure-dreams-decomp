#ifndef DUNGEON_MONSTER_WEADOG_H
#define DUNGEON_MONSTER_WEADOG_H

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"



void advance_timed_actor_hop(void *action, void *motion, SpriteFrameState *sprite, void *actor);
void advance_timed_hop_and_recover(void *motion_state, void *motion, SpriteFrameState *sprite, void *actor);
void update_weadog_timed_move(void *action, void *motion, SpriteFrameState *sprite, void *actor);

#endif
