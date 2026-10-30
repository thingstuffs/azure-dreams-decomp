#ifndef DUNGEON_MONSTER_MANDARA_H
#define DUNGEON_MONSTER_MANDARA_H

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

/* Monster-owned imports; preserve their registered declaration contracts. */
extern u8 mandara_direction_frames[];



void advance_actor_action_animation_to_completion(ActorRecord *action, ObjectPosition *actor_id, SpriteFrameState *animation, ActorRecord *actor);

void fade_remove_entity_and_update_tile(ActorRecord *fade_state, ObjectPosition *unused, SpriteFrameState *visual_data, ActorRecord *entity);

void update_long_actor_action(ActorRecord *self_object, ObjectPosition *aux_entity, SpriteFrameState *sprite, ActorRecord *entity);

/* Callback entry points. */
s32 draw_layered_wavy_object_strips(void *object_data, void *unused, void *appearance);
void advance_actor_replacement_sequence(void *effect, s32 unused, void *primitive);
void blend_animation_palette_and_complete(void *effect);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
void advance_action_through_recovery(ActorRecord *action_state, ObjectPosition *transform, SpriteFrameState *sprite, ActorRecord *actor);
void *create_mandara_actor_with_parts(s32 spawn_flags, s16 pos_x, s16 pos_y, s16 part_a_value);
void *spawn_mandara_in_slot_c(s32 spawn_flags, s16 tile_x, s16 tile_y, s16 spawn_height);
void *spawn_mandara_in_slot_d(s16 flags, s16 kind_id, s16 tile_y, s16 spawn_height);
void *spawn_mandara_slot_a(s16 spawn_flags, s16 tile_x, s16 tile_y, s32 heading);

#endif
