#ifndef DUNGEON_MONSTER_CYCLONE_H
#define DUNGEON_MONSTER_CYCLONE_H

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

/* Monster-owned imports; preserve their registered declaration contracts. */
extern u8 cyclone_direction_frames[];

void advance_cyclone_frame_effect(u16 *anim_state, u32 *motion, u16 *sprite);


struct S_8017294C_1;
void advance_backward_forward_motion(void *action, ObjectPosition *motion, SpriteFrameState *animation, ActorRecord *actor);

void attempt_actor_directional_action(struct S_8017294C_1 *action_state, s32 action_ctx, SpriteFrameState *sprite, ActorRecord *actor);



void fade_reshape_and_remove_entity(void *fade_state, ObjectPosition *position, SpriteFrameState *sprite, void *entity);



void advance_target_interaction(void *action, void *scene, SpriteFrameState *sprite, ActorRecord *actor);
void update_actor_action_and_flags(void *actor, void *action_ctx, SpriteFrameState *anim, ActorRecord *entity);

void update_actor_animation(void *actor_arg, void *context_arg, SpriteFrameState *sprite_arg, void *stats_arg);

/* Callback entry points. */
void advance_eight_tick_animation(u16 *anim, u32 *motion, u16 *sprite);

#endif
