#ifndef DUNGEON_MONSTER_U_BOAT_H
#define DUNGEON_MONSTER_U_BOAT_H

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

/* Monster-owned imports; preserve their registered declaration contracts. */
extern u8 uboat_behavior_entry[];



void advance_actor_action(ActorRecord *action, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *entity);

void leave_actor_aura_mode(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *entity);
void update_actor_timed_tile_motion(void *action, ObjectPosition *motion, SpriteFrameState *sprite, void *actor);



void advance_staged_actor_movement(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *record, ActorRecord *actor);
void enter_actor_aura_mode(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);
void update_actor_visual_motion(ActorRecord *body, ObjectPosition *motion_arg, SpriteFrameState *sprite);
void update_rotating_actor_aura(void *effect, ObjectPosition *position, SpriteFrameState *visual);

void update_actor_movement_state(ActorRecord *body, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor_arg);

void choose_and_execute_actor_step(ActorRecord *work_data, ObjectPosition *action_context, SpriteFrameState *position, ActorRecord *actor);

void create_owner_linked_directional_object(ActorRecord *owner_data, ObjectPosition *source_position, SpriteFrameState *source_sprite);
void update_actor_turn_and_action(void *entity, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *actor);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
#include "records/Rec_func_800A9E70_arg0.h"
s32 try_turn_actor_toward_target(Rec_func_800A9E70_arg0 *action_state, ObjectPosition *action_context, SpriteFrameState *target, ActorRecord *actor);

#endif
