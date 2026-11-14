#ifndef DUNGEON_MONSTER_KID_H
#define DUNGEON_MONSTER_KID_H

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"



void advance_stored_actor_path(ActorRecord *body, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *actor);

void wait_for_kid_mp_recovery(ActorRecord *action, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *entity);
void update_actor_action_and_animation(ActorRecord *controller_in, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);



void advance_kid_defeat_sequence(ActorRecord *body, ObjectPosition *motion, SpriteFrameState *sprite, void *entity);
void update_staged_actor_movement(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *tile, ActorRecord *actor);

/* Callback entry points. */
typedef struct RandomlyRotatedOffsetEffectBody {
    union { u8 u; s8 s; } unk_00;
    union { u8 u; s8 s; } unk_01;
    union { u8 u; s8 s; } unk_02;
    u8 pad_03[0x17];
    union { s16 s; u16 u; } unk_1A;
} RandomlyRotatedOffsetEffectBody;
void animate_effect_colors(RandomlyRotatedOffsetEffectBody *effect_state, ObjectPosition *unused, SpriteFrameState *primitive);
void wait_for_kid_action_slot(ActorRecord *entity_data, ObjectPosition *unused_position, SpriteFrameState *unused_sprite, ActorRecord *other_data);

void create_randomly_rotated_offset_effect(void *unused_ptr, ObjectPosition *source_pos, SpriteFrameState *unused_value, s16 scale);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
void update_kid_recoil(ActorRecord *body, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);

void finish_kid_effect_and_tint(u8 *task, ObjectPosition *context, SpriteFrameState *input);
void begin_kid_attack_action(ActorRecord *action_state, ObjectPosition *context, SpriteFrameState *animation, ActorRecord *entity);

void advance_item_action_sequence(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);

#endif
