#ifndef DUNGEON_MONSTER_HIKEWNE_H
#define DUNGEON_MONSTER_HIKEWNE_H

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "records/Rec_func_800A9E70_arg0.h"

/* Monster-owned imports; preserve their registered declaration contracts. */
extern u8 hikewne_alt_direction_frames[];

void choose_hikewne_move(ActorRecord *move_data, ObjectPosition *context, SpriteFrameState *position_data, ActorRecord *actor_data);

struct Rec_D_80082E80;
/* Slows directional motion, then recenters the entity on its tile. */
void update_hikewne_recoil(ActorRecord *motion_state, ObjectPosition *motion, struct Rec_D_80082E80 *tile_state, ActorRecord *entity);


void update_sleeping_hikewne(ActorRecord *action, ObjectPosition *context, SpriteFrameState *entity, ActorRecord *actor);

struct S_80173588_0;
void update_hikewne_hop_and_shrink(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);



void update_actor_movement_and_ground_height(void *actor, ObjectPosition *motion, SpriteFrameState *sprite);
void update_actor_movement_facing(void *entity, ObjectPosition *motion, SpriteFrameState *sprite);
void update_entity_behavior_movement_and_ground(void *entity, ObjectPosition *motion, SpriteFrameState *sprite);
void update_entity_behavior_movement_and_grounding(void *entity, ObjectPosition *motion, SpriteFrameState *sprite);
void update_entity_behavior_movement_and_height(ActorRecord *body, ObjectPosition *motion, SpriteFrameState *sprite);
void update_entity_ground_animation(void *entity, ObjectPosition *motion, SpriteFrameState *sprite);
void update_entity_movement_and_ground(ActorRecord *entity, ObjectPosition *motion, SpriteFrameState *sprite);

void move_hikewne_to_tile(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *source, ActorRecord *target);

void update_hikewne_actor_behavior(ActorRecord *actor_arg, ObjectPosition *context_arg, SpriteFrameState *sprite_arg, ActorRecord *stats_arg);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
void advance_actor_along_queued_path(ActorRecord *motion, ObjectPosition *unused, SpriteFrameState *actor, ActorRecord *move_state);
void begin_hikewne_attack(ActorRecord *action_state, ObjectPosition *effect_context, SpriteFrameState *update_context, ActorRecord *entity);
s32 relink_hikewne_path(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, s32 force_state_arg);
s32 try_hikewne_attack(ActorRecord *action, ObjectPosition *effect, SpriteFrameState *target, ActorRecord *actor_data);

void advance_hikewne_attack_animation(ActorRecord *action_data, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor_data);

#endif
