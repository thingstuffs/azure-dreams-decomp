#ifndef DUNGEON_MONSTER_SABER_H
#define DUNGEON_MONSTER_SABER_H

#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/entity.h"

typedef struct SaberTileOffset {
    s16 x;
    union { s16 s; u16 u; } y;
} SaberTileOffset;

typedef struct SaberTileOffsets {
    SaberTileOffset entries[8];
} SaberTileOffsets;

/* Lifetime, facing, and reference position for selected-item effects. */
typedef struct SelectedItemActionEffectBody {
    u8 pad_00[0x94];
    union { s16 s; u16 u; } facing;
    u16 ticks_remaining;
    u8 pad_98[0x10];
    void *reference_position;
} SelectedItemActionEffectBody;

extern SaberTileOffsets saber_direction_tile_offsets;

/* Monster-owned imports; preserve their registered declaration contracts. */
extern s32 saber_behavior_entry;
extern u8 saber_direction_frames[];
extern u8 saber_direction_frames_2[];





void advance_actor_hop_and_complete(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);


void advance_timed_entity_hop(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *map_entity, ActorRecord *actor);
void finish_saber_tile_hop(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *entity);
void advance_saber_hit_recoil(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *actor, ActorRecord *entity);

void update_actor_directional_animation(ActorRecord *actor_in, ObjectPosition *position, SpriteFrameState *target, ActorRecord *entity_in);





void advance_directional_effect_action(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);
void advance_timed_animation_and_cleanup(ActorRecord *sequence, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);



void advance_tile_movement_and_completion(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *map_entity, ActorRecord *actor);
void move_toward_sprite_tile_and_complete(void *action, void *motion, SpriteFrameState *sprite, ActorRecord *actor);
void update_actor_tile_movement(void *action, void *motion, SpriteFrameState *sprite, ActorRecord *actor);
void update_tile_movement_and_action_completion(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);

void finish_saber_tile_move(ActorRecord *entity_arg, ObjectPosition *motion, SpriteFrameState *check_arg, ActorRecord *actor_arg);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
void initialize_actor_facing_sprite(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *orientation);

void resolve_saber_hits_on_target_tile(void *node, s32 target_x, s32 target_y, s32 target_height);

void begin_saber_action_and_spend_turn(ActorRecord *action_state, ObjectPosition *effect_arg, SpriteFrameState *anim_state, ActorRecord *actor);

#endif
