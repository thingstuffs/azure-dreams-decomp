#ifndef DUNGEON_MONSTER_KEWNE_UNCACHED_H
#define DUNGEON_MONSTER_KEWNE_UNCACHED_H

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"



void update_jump_movement_and_landing(void *jump, ObjectPosition *motion, SpriteFrameState *sprite, void *actor);
void update_staged_movement_height_and_animation(void *motion, ObjectPosition *velocity, SpriteFrameState *sprite, ActorRecord *actor);

#endif
