#ifndef DUNGEON_MONSTER_BLUME_H
#define DUNGEON_MONSTER_BLUME_H

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

/* Monster-owned imports; preserve their registered declaration contracts. */
extern u8 blume_direction_frames[];
extern u8 blume_direction_frames_2[];



void update_damped_height_effect(void *state, void *position, SpriteFrameState *object);
void update_growing_colliding_effect(void *effect, void *position, SpriteFrameState *sprite);

/* Callback entry points. */
void update_fading_motion_effect(void *effect, void *transform, void *color);

#endif
