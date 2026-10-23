#ifndef DUNGEON_ACTOR_MOTION_H
#define DUNGEON_ACTOR_MOTION_H

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"



void update_airborne_actor_motion(void *action, ObjectPosition *motion, SpriteFrameState *sprite, EntityRec *actor);



void update_actor_facing_and_lifecycle(void *state, ObjectPosition *motion, SpriteFrameState *part);
void update_rising_landing_effect(void *effect, ObjectPosition *motion, SpriteFrameState *sprite);

#endif
