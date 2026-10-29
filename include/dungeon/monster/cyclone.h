#ifndef DUNGEON_MONSTER_CYCLONE_H
#define DUNGEON_MONSTER_CYCLONE_H

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

/* Monster-owned imports; preserve their registered declaration contracts. */
extern u8 cyclone_direction_frames[];

void advance_cyclone_frame_effect(u16 *anim_state, u32 *motion, u16 *sprite);


struct S_8017294C_1;
void advance_backward_forward_motion(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *animation, ActorRecord *actor);

void attempt_actor_directional_action(ActorRecord *action_state, ObjectPosition *action_ctx, SpriteFrameState *sprite, ActorRecord *actor);



void fade_reshape_and_remove_entity(void *fade_state, ObjectPosition *position, SpriteFrameState *sprite, void *entity);



void advance_target_interaction(ActorRecord *action, ObjectPosition *scene, SpriteFrameState *sprite, ActorRecord *actor);
void update_actor_action_and_flags(ActorRecord *actor, ObjectPosition *action_ctx, SpriteFrameState *anim, ActorRecord *entity);

void update_actor_animation(ActorRecord *actor_arg, ObjectPosition *context_arg, SpriteFrameState *sprite_arg, ActorRecord *stats_arg);

/* Callback entry points. */
void advance_eight_tick_animation(u16 *anim, u32 *motion, u16 *sprite);
s32 request_random_slot_effect(ActorRecord *actor);
void * create_randomized_motion_object(ActorRecord *owner, ObjectPosition *initial_state);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
void advance_path_motion(void *motion, ObjectPosition *unused, SpriteFrameState *entity, void *path_state);

void update_radial_motion_or_complete(u16 *motion, s32 *position, SpriteFrameState *object);

#endif
