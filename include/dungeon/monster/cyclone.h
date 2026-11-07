#ifndef DUNGEON_MONSTER_CYCLONE_H
#define DUNGEON_MONSTER_CYCLONE_H

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

/* Monster-owned imports; preserve their registered declaration contracts. */
extern u8 cyclone_direction_frames[];
extern u8 cyclone_view_direction_entries[];

/* Radial motion state stored at node body +0. */
typedef struct RandomizedMotionObjectBody {
    u16 update_count;
    u8 pad_02[0x2];
    s16 phase;
    u16 radius;
    u16 radius_growth;
} RandomizedMotionObjectBody;

/* Direction, delay, and scale phase for the delayed directional render object. */
typedef struct DirectionalRenderObjectBody {
    union { s16 s; u16 u; } phase;
    union { u16 s; s16 u; } ticks;
    union { s16 s; u16 u; } facing_angle;
} DirectionalRenderObjectBody;

void advance_cyclone_frame_effect(u16 *anim_state, u32 *motion, u16 *sprite);

void advance_backward_forward_motion(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *animation, ActorRecord *actor);

void attempt_actor_directional_action(ActorRecord *action_state, ObjectPosition *action_ctx, SpriteFrameState *sprite, ActorRecord *actor);

void fade_reshape_and_remove_entity(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, void *entity);

void advance_target_interaction(ActorRecord *action, ObjectPosition *scene, SpriteFrameState *sprite, ActorRecord *actor);
void update_actor_action_and_flags(ActorRecord *actor, ObjectPosition *action_ctx, SpriteFrameState *anim, ActorRecord *entity);

void update_actor_animation(ActorRecord *actor_arg, ObjectPosition *context_arg, SpriteFrameState *sprite_arg, ActorRecord *stats_arg);

/* Callback entry points. */
void advance_eight_tick_animation(u16 *anim, u32 *motion, u16 *sprite);
s32 request_random_slot_effect(ActorRecord *actor);
void *create_randomized_motion_object(ActorRecord *owner, ObjectPosition *initial_state);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
void advance_path_motion(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);

void update_radial_motion_or_complete(RandomizedMotionObjectBody *motion, s32 *position, SpriteFrameState *object);
void grow_object_after_delay(DirectionalRenderObjectBody *animation, ObjectPosition *unused_position, SpriteFrameState *object);

void clear_actor_action_flag_and_animate(ActorRecord *action_state, ObjectPosition *action_context, SpriteFrameState *animation, ActorRecord *actor);
void finish_actor_tile_move_and_check_trap(ActorRecord *action_state, ObjectPosition *action_ctx, SpriteFrameState *sprite, ActorRecord *actor);
s32 search_ahead_and_start_action(ActorRecord *action_state, ObjectPosition *action_context, SpriteFrameState *sprite, ActorRecord *actor);
void update_action_state_direction_specific(ActorRecord *action_state, ObjectPosition *action_param, SpriteFrameState *sprite, ActorRecord *actor);

struct Actor;
void update_actor_direction_and_ground(struct Actor *input_actor, ObjectPosition *input_motion, SpriteFrameState *input_entity);

#endif
