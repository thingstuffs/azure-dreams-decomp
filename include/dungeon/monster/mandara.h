#ifndef DUNGEON_MONSTER_MANDARA_H
#define DUNGEON_MONSTER_MANDARA_H

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

/* Monster-owned imports; preserve their registered declaration contracts. */
extern u8 mandara_direction_frames[];



void advance_actor_action_animation_to_completion(void *action, s32 actor_id, SpriteFrameState *animation, ActorRecord *actor);

void fade_remove_entity_and_update_tile(void *fade_state, void *unused, SpriteFrameState *visual_data, ActorRecord *entity);

void update_long_actor_action(void *self_object, void *aux_entity, SpriteFrameState *sprite, void *entity);

/* Callback entry points. */
s32 draw_layered_wavy_object_strips(void *object_data, void *unused, void *appearance);
void advance_actor_replacement_sequence(void *effect, s32 unused, void *primitive);
void blend_animation_palette_and_complete(void *effect);

#endif
