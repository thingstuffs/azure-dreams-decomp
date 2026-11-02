#ifndef DUNGEON_MONSTER_DREAMIN_H
#define DUNGEON_MONSTER_DREAMIN_H

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

/* Monster-owned imports; preserve their registered declaration contracts. */
extern u8 dreamin_direction_frames[];



s32 attempt_actor_transition(ActorRecord *state, ObjectPosition *action_id, SpriteFrameState *sprite, ActorRecord *actor);
void advance_timed_directional_movement(ActorRecord *body, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *entity);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
void *damp_effect_motion_and_fade_sprite(s16 init_flags, s16 value_24, s16 value_25, s16 value_0a);
void *move_and_fade_effect_sprite(s16 spawn_flags, s16 grid_x, s16 grid_y, s16 type_id);
void *spawn_dreamin_slot_b(s16 spawn_flags, s16 spawn_x, s16 spawn_y, s16 initial_value);

#endif
