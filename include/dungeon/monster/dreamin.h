#ifndef DUNGEON_MONSTER_DREAMIN_H
#define DUNGEON_MONSTER_DREAMIN_H

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

/* Monster-owned imports; preserve their registered declaration contracts. */
extern u8 dreamin_direction_frames[];



s32 attempt_actor_transition(void *state, s32 action_id, SpriteFrameState *sprite, ActorRecord *actor);
void advance_timed_directional_movement(void *action, void *motion, SpriteFrameState *sprite, void *entity);

#endif
