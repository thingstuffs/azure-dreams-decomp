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

void advance_actor_staged_animation(ActorRecord *action_data, ObjectPosition *motion, SpriteFrameState *animation, ActorRecord *actor);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
struct T_80170874_S_80DB9000_1;
struct T_80170874_S_80DB9000_2;
struct T_80170874_S_80DB9000_3;
void project_sprite_entries_to_quads(struct T_80170874_S_80DB9000_1 *sprite_size, struct T_80170874_S_80DB9000_2 *position, struct T_80170874_S_80DB9000_3 *sprite, s16 depth_bias);

#endif
