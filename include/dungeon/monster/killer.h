#ifndef DUNGEON_MONSTER_KILLER_H
#define DUNGEON_MONSTER_KILLER_H

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

/* Monster-owned imports; preserve their registered declaration contracts. */
extern u8 killer_direction_frames[];




void advance_timed_directional_animation(void *action_state, s32 actor_id, SpriteFrameState *animation, ActorRecord *actor);



void advance_directional_lift_effect(void *action_record, ObjectPosition *motion_data, SpriteFrameState *status_record, void *entity_data);

#endif
