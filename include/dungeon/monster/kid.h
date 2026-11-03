#ifndef DUNGEON_MONSTER_KID_H
#define DUNGEON_MONSTER_KID_H

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"



void advance_stored_actor_path(ActorRecord *body, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *actor);

void advance_entity_animation_actions(ActorRecord *action, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *entity);
void update_actor_action_and_animation(ActorRecord *controller_in, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);



void advance_fading_directional_entity(ActorRecord *body, ObjectPosition *motion, SpriteFrameState *sprite, void *entity);
void update_staged_actor_movement(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *tile, ActorRecord *actor);

/* Callback entry points. */
typedef struct RandomlyRotatedOffsetEffectBody {
    union { u8 u; s8 s; } unk_00;
    union { u8 u; s8 s; } unk_01;
    union { u8 u; s8 s; } unk_02;
    u8 pad_03[0x17];
    union { s16 s; u16 u; } unk_1A;
} RandomlyRotatedOffsetEffectBody;
void animate_effect_colors(RandomlyRotatedOffsetEffectBody *effect_state, ObjectPosition *unused, void *primitive);
void initialize_counted_entity_action(ActorRecord *entity_data, ObjectPosition *unused_position, SpriteFrameState *unused_sprite, ActorRecord *other_data);

void create_randomly_rotated_offset_effect(void *unused_ptr, ObjectPosition *source_pos, SpriteFrameState *unused_value, s16 scale);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
void complete_directional_hop_to_tile(ActorRecord *body, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);

void blend_effect_channels_to_gray(u8 *task, ObjectPosition *context, SpriteFrameState *input);
void initialize_status_gated_action(ActorRecord *action_state, ObjectPosition *context, SpriteFrameState *animation, ActorRecord *entity);

#endif
