#ifndef DUNGEON_MONSTER_IFRIT_H
#define DUNGEON_MONSTER_IFRIT_H

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

/* Monster-owned imports; preserve their registered declaration contracts. */
extern u8 ifrit_direction_frames[];



void advance_actor_animation_and_restore(void *action, s32 actor_id, SpriteFrameState *sprite, ActorRecord *actor);

#endif
