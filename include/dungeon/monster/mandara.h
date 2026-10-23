#ifndef DUNGEON_MONSTER_MANDARA_H
#define DUNGEON_MONSTER_MANDARA_H

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

/* Monster-owned imports; preserve their registered declaration contracts. */
extern u8 mandara_direction_frames[];



void advance_actor_action_animation_to_completion(void *action, s32 actor_id, SpriteFrameState *animation, ActorRecord *actor);

void fade_remove_entity_and_update_tile(void *fade_state, void *unused, SpriteFrameState *visual_data, ActorRecord *entity);

#endif
