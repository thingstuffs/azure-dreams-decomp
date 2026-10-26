#ifndef DUNGEON_MONSTER_BATTNEL_H
#define DUNGEON_MONSTER_BATTNEL_H

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

/* Monster-owned imports; preserve their registered declaration contracts. */
extern u8 battnel_direction_frames[];



void decelerate_and_center_actor_on_tile(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);

#endif
