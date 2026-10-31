#ifndef DUNGEON_MONSTER_HIKEWNE_H
#define DUNGEON_MONSTER_HIKEWNE_H

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "records/Rec_func_800A9E70_arg0.h"

/* Monster-owned imports; preserve their registered declaration contracts. */
extern u8 hikewne_alt_direction_frames[];

void select_movement_direction_and_advance(ActorRecord *move_data, ObjectPosition *context, SpriteFrameState *position_data, ActorRecord *actor_data);


void advance_actor_state_sequence(ActorRecord *action, ObjectPosition *context, SpriteFrameState *entity, ActorRecord *actor);

struct S_80173588_0;
void reset_state_field_a_2(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);



void update_actor_movement_and_ground_height(void *actor, ObjectPosition *motion, SpriteFrameState *sprite);
void update_actor_movement_facing(void *entity, ObjectPosition *motion, SpriteFrameState *sprite);
void update_entity_behavior_movement_and_ground(void *entity, ObjectPosition *motion, SpriteFrameState *sprite);
void update_entity_behavior_movement_and_grounding(void *entity, ObjectPosition *motion, SpriteFrameState *sprite);
void update_entity_behavior_movement_and_height(ActorRecord *body, ObjectPosition *motion, SpriteFrameState *sprite);
void update_entity_ground_animation(void *entity, ObjectPosition *motion, SpriteFrameState *sprite);
void update_entity_movement_and_ground(void *entity, ObjectPosition *motion, SpriteFrameState *sprite);

void select_state_table_with_flagged_offset(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *source, ActorRecord *target);

void update_actor_behavior_animation_and_facing(ActorRecord *actor_arg, ObjectPosition *context_arg, SpriteFrameState *sprite_arg, ActorRecord *stats_arg);

#endif
