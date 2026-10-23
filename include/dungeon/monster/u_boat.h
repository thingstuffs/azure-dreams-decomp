#ifndef DUNGEON_MONSTER_U_BOAT_H
#define DUNGEON_MONSTER_U_BOAT_H

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

/* Monster-owned imports; preserve their registered declaration contracts. */
extern u8 uboat_behavior_entry[];



void advance_actor_action(void *action, void *context, SpriteFrameState *sprite, ActorRecord *entity);

void leave_actor_aura_mode(void *state, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *entity);
void update_actor_timed_tile_motion(void *action, void *motion, SpriteFrameState *sprite, void *actor);



void advance_staged_actor_movement(void *action, ObjectPosition *motion, SpriteFrameState *record, ActorRecord *actor);
void enter_actor_aura_mode(void *actor_state, ObjectPosition *position, SpriteFrameState *sprite, void *actor_info);
void update_actor_visual_motion(void *object_arg, ObjectPosition *motion_arg, SpriteFrameState *part_arg);
void update_rotating_actor_aura(void *effect, ObjectPosition *position, SpriteFrameState *visual);

#endif
