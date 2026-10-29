#ifndef DUNGEON_PLAYER_INPUT_H
#define DUNGEON_PLAYER_INPUT_H

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

/* Four words copied from the previous dungeon turn status. */
extern s32 D_800E4948[4];



/* Eight camera-relative facing entries, ending at player_push_start_frames. */
extern u8 player_wait_frames[8];

s32 has_action_input_without_modifier(void);

void handle_carrying_player_input(void *object, void *aux_entity, SpriteFrameState *sprite, void *entity);

/* The turn coordinator supplies all four actor contexts; this input step only reads actor. */
s32 update_sound_settings_from_pad(void *actor, void *unused_motion,
    void *unused_sprite, void *unused_stats);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
void handle_player_input(void *actor, void *motion, register void *sprite, void *stats);

#endif
