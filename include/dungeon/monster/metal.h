#ifndef DUNGEON_MONSTER_METAL_H
#define DUNGEON_MONSTER_METAL_H

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"







void advance_timed_actor_animation_and_restore(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);

#endif
