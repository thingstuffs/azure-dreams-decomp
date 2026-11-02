#ifndef DUNGEON_MONSTER_KILLER_H
#define DUNGEON_MONSTER_KILLER_H

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

/* Monster-owned imports; preserve their registered declaration contracts. */
extern u8 killer_direction_frames[];




void advance_timed_directional_animation(ActorRecord *action_state, ObjectPosition *actor_id, SpriteFrameState *animation, ActorRecord *actor);



void advance_directional_lift_effect(ActorRecord *action_record, ObjectPosition *motion_data, SpriteFrameState *status_record, void *entity_data);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
void *spawn_killer(s16 flags, s32 kind_id, s32 variant, s32 spawn_value);
void *spawn_killer_slot_b(s16 spawn_flags, s32 grid_x, s32 grid_y, s16 part_value);
void *spawn_killer_slot_c(s16 init_flags, s32 pos_x, s32 pos_y, s16 init_value);
void *spawn_killer_slot_d(s16 setup_bits, s32 grid_x, s32 grid_y, s16 placement_value);
void *spawn_killer_slot_f(s16 kind_flags, s32 part_value_24, s32 part_value_25, s16 part_value_0a);
void update_eligible_actor_action_alt(ActorRecord *action_state, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *actor);
void update_entity_action_facing(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *entity);
s32 validate_direction_and_initialize_action(ActorRecord *action_state, ObjectPosition *action_id, SpriteFrameState *sprite, ActorRecord *actor);

#endif
