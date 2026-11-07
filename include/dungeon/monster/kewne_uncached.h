#ifndef DUNGEON_MONSTER_KEWNE_UNCACHED_H
#define DUNGEON_MONSTER_KEWNE_UNCACHED_H

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"



struct S_80173408_0;
void update_jump_movement_and_landing(struct S_80173408_0 *jump, ObjectPosition *motion, SpriteFrameState *sprite, void *actor);
struct S_80173930_0;
void update_staged_movement_height_and_animation(struct S_80173930_0 *motion, ObjectPosition *velocity, SpriteFrameState *sprite, ActorRecord *actor);

void update_actor_behavior_2(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *object, ActorRecord *actor);

#endif
