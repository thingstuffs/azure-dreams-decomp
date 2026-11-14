#ifndef DUNGEON_MONSTER_KEWNE_H
#define DUNGEON_MONSTER_KEWNE_H

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"



void advance_actor_path_and_facing(ActorRecord *body, ObjectPosition *unused, SpriteFrameState *sprite, ActorRecord *actor);

void update_sleeping_kewne(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *render_record, ActorRecord *actor_state);
void advance_kewne_trail_attack(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);
void advance_kewne_ellipse_attack(ActorRecord *body, ObjectPosition *movement, SpriteFrameState *sprite, ActorRecord *actor);

void advance_kewne_leap_attack(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);

void update_actor_animation_and_behavior(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *entity);

/* Directional frame entries; the full allocation extent is not inferred. */
extern u8 kewne_direction_frames[];

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
void create_linked_child_object(ActorRecord *parent_state);
void create_linked_source_object(ActorRecord *source_actor);
void create_ellipse_ring_effect(EntityRec *parent, s32 effect_param, u8 *effect_data);
void update_kewne_actor(ActorRecord *actor, ObjectPosition *position, SpriteFrameState *sprite);

void *spawn_kewne_actor(s16 spawn_flags, s16 grid_x, s16 grid_y, s16 height);

void update_kewne_recoil(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);

void advance_turn_animation_and_restore_heading(ActorRecord *actor, ObjectPosition *unused, SpriteFrameState *animation, ActorRecord *transform_in);

void start_kewne_attack_action(ActorRecord *controller, ObjectPosition *action_context, SpriteFrameState *sprite, ActorRecord *actor);

#include "shared/dungeon_moving_views.h"
void update_effect_fade_and_history(void *effect, MovingPosition *position, SpriteFrameState *primitive);

void update_kewne_charge_counter(ActorRecord *actor_state, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);

#endif
