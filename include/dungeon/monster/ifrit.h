#ifndef DUNGEON_MONSTER_IFRIT_H
#define DUNGEON_MONSTER_IFRIT_H

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

/* Monster-owned imports; preserve their registered declaration contracts. */
extern u8 ifrit_direction_frames[];



void advance_actor_animation_and_restore(ActorRecord *action, ObjectPosition *actor_id, SpriteFrameState *sprite, ActorRecord *actor);

/* Callback entry points. */
s32 render_linked_items_as_textured_strips(u8 *item_data);
void tick_object_motion_and_expire(void *object_data, void *motion_data, void *work_data);

#endif
