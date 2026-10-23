#ifndef DUNGEON_MONSTER_PULUNPA_H
#define DUNGEON_MONSTER_PULUNPA_H

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

/* Monster-owned imports; preserve their registered declaration contracts. */
extern u8 pulunpa_direction_frames[];








void advance_directional_action_and_reset(void *action, ObjectPosition *motion, SpriteFrameState *anim, ActorRecord *actor);



void animate_hop_to_actor_tile(void *action, void *motion, SpriteFrameState *sprite, ActorRecord *actor);

#endif
