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

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
void create_linked_child_object(ActorRecord *parent_state);
void create_linked_source_object(ActorRecord *source_actor);
void create_parent_position_effect(EntityRec *parent, s32 effect_param, u8 *effect_data);
void update_actor_callbacks_and_ground(void *actor, ObjectPosition *position, SpriteFrameState *sprite);

void *create_grid_position_entity(s16 spawn_flags, s16 grid_x, s16 grid_y, s16 height);

void decay_motion_and_align_actor(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);

void advance_turn_animation_and_restore_heading(ActorRecord *actor, ObjectPosition *unused, SpriteFrameState *animation, ActorRecord *transform_in);

void start_kewne_attack_action(ActorRecord *controller, ObjectPosition *action_context, SpriteFrameState *sprite, ActorRecord *actor);

#endif
