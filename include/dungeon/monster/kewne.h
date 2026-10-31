#ifndef DUNGEON_MONSTER_KEWNE_H
#define DUNGEON_MONSTER_KEWNE_H

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"



void advance_actor_path_and_facing(ActorRecord *body, ObjectPosition *unused, SpriteFrameState *sprite, ActorRecord *actor);

void advance_actor_action_and_refresh_animation(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *render_record, ActorRecord *actor_state);
void update_movement_height_and_animation(void *action, ObjectPosition *motion, SpriteFrameState *sprite, void *actor);
void update_staged_movement_and_idle(ActorRecord *body, ObjectPosition *movement, SpriteFrameState *sprite, ActorRecord *actor);

void update_three_state_directional_motion(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);

void update_actor_animation_and_behavior(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *entity);

/* Directional frame entries; the full allocation extent is not inferred. */
extern u8 kewne_direction_frames[];

#endif
