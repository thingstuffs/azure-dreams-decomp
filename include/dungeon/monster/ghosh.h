#ifndef DUNGEON_MONSTER_GHOSH_H
#define DUNGEON_MONSTER_GHOSH_H

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_moving_views.h"

/* Monster-owned imports; preserve their registered declaration contracts. */
extern u8 ghosh_direction_frames[];
extern u8 ghosh_ready_action_frames[];

void create_boss_child_effect(void *parent_data, MovingPosition *source_pos, void *sprite_template);
void create_boss_directional_effect(void *source, s16 angle, s32 initial_value, s32 unused, s16 spread_mode);
void release_secondary_overlay_object(void);


void update_boss_actor_action(void *actor, void *context, SpriteFrameState *sprite, ActorRecord *entity);



void update_actor_animation_movement_and_terrain(void *entity, ObjectPosition *motion, void *sprite);
void update_boss_actor_movement(void *entity, ObjectPosition *motion, SpriteFrameState *sprite);

#endif
