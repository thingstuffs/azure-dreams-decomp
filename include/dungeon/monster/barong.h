#ifndef DUNGEON_MONSTER_BARONG_H
#define DUNGEON_MONSTER_BARONG_H

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

/* Monster-owned imports; preserve their registered declaration contracts. */
extern u8 barong_direction_frames[];







void update_actor_movement_animation_states_completes_timed_action(void *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);

void update_motion_and_grow_sprite(void *motion, void *position, SpriteFrameState *sprite);





void advance_timed_actor_animation(void *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);



void advance_arcing_actor_move(void *action, void *motion, SpriteFrameState *sprite, ActorRecord *actor);
void hop_actor_and_restore_scale(void *action, void *motion, SpriteFrameState *sprite, ActorRecord *actor);
void update_actor_hop_action(void *action, void *motion, SpriteFrameState *sprite, ActorRecord *actor);
void update_hop_motion_and_completion(void *action, void *motion, SpriteFrameState *sprite, ActorRecord *actor);
void update_tile_centering_motion_animation_restores_actor_timer_expires(void *action, void *motion, SpriteFrameState *sprite, ActorRecord *actor);
void update_timed_hop_and_landing(void *action, void *motion, SpriteFrameState *sprite, ActorRecord *actor);

/* Callback entry points. */
void update_motion_and_terrain_collision(void *motion, void *position, void *object);

#endif
