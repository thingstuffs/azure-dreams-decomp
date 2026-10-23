#ifndef DUNGEON_MONSTER_MAXIMUM_H
#define DUNGEON_MONSTER_MAXIMUM_H

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"



void advance_actor_action_animation_and_cleanup(void *action, s32 actor_id, SpriteFrameState *animation, ActorRecord *actor);

#endif
