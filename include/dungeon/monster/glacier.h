#ifndef DUNGEON_MONSTER_GLACIER_H
#define DUNGEON_MONSTER_GLACIER_H

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

/* Monster-owned imports; preserve their registered declaration contracts. */
extern u8 glacier_direction_frames[];




void update_staged_item_movement(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *target, ActorRecord *actor);



void update_action_and_check_forward_tile(ActorRecord *actor, ObjectPosition *motion, SpriteFrameState *animation, ActorRecord *entity);



void update_item_hop_animation(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);

void update_actor_timed_effects(ActorRecord *actor_arg, ObjectPosition *context_arg, SpriteFrameState *sprite_arg, ActorRecord *stats_arg);

/* Callback entry points. */
void advance_item_motion_collision(void *motion, void *position, void *update_arg);
void update_monster_appearance_motion(ActorRecord *entity_arg, void *motion_arg, SpriteFrameState *monster_arg);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
void advance_selected_item_action_2(void *action, ObjectPosition *position, SpriteFrameState *sprite, void *actor);

#include "records/Rec_func_801744DC_arg0.h"
#include "records/Rec_func_801744DC_arg1.h"
void initialize_item_sprite_frame(void *object, void *unused, SpriteFrameState *sprite, void *orientationSource);
void spawn_directional_effect(Rec_func_801744DC_arg0 *source, Rec_func_801744DC_arg1 *origin);
void spawn_directional_particle(Rec_func_801744DC_arg0 *source, Rec_func_801744DC_arg1 *origin);

#endif
