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

extern SaberTileOffsets saber_direction_tile_offsets;

/* Monster-owned imports; preserve their registered declaration contracts. */
extern s32 saber_behavior_entry;
extern u8 saber_direction_frames[];
extern u8 saber_direction_frames_2[];





void advance_actor_hop_and_complete(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);


void advance_timed_entity_hop(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *map_entity, ActorRecord *actor);
void finish_saber_tile_hop(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *entity);
void move_actor_briefly_and_realign(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *actor, ActorRecord *entity);

void update_actor_directional_animation(ActorRecord *actor_in, void *actor_index, SpriteFrameState *target, ActorRecord *entity_in);





void advance_directional_effect_action(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);
void advance_timed_animation_and_cleanup(ActorRecord *sequence, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);



void advance_tile_movement_and_completion(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *map_entity, ActorRecord *actor);
void move_toward_sprite_tile_and_complete(void *action, void *motion, SpriteFrameState *sprite, ActorRecord *actor);
void update_actor_tile_movement(void *action, void *motion, SpriteFrameState *sprite, ActorRecord *actor);
void update_tile_movement_and_action_completion(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);

void reset_eligible_entity_state(void *entity_arg, void *motion, void *check_arg, void *actor_arg);

#endif
