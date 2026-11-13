#ifndef INCLUDE_DUNGEON_ACTOR_TIMED_VISUAL_SLOT_F_H
#define INCLUDE_DUNGEON_ACTOR_TIMED_VISUAL_SLOT_F_H

/* Contracts owned by src/dungeon/func_80F90A60.c. */
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern u8 timed_visual_slot_f_return_frames[];
extern u8 timed_visual_slot_f_wait_frames[];

void update_actor_timed_visual(ActorRecord *state_input, ObjectPosition *motion_input, SpriteFrameState *animation_input, ActorRecord *actor_input);

#endif
