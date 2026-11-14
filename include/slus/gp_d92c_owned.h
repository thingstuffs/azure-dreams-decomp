#ifndef SLUS_GP_D92C_OWNED_H
#define SLUS_GP_D92C_OWNED_H

/* Present C interface; historical filename and TU boundary remain inferred. */
#include "shared/runtime_dispatch.h"
#include "common.h"
#include "shared/game_work.h"
#include "slus/animation_tick_data.h"
#include "slus/saved_volume_scales_data.h"

extern short camera_shoulder_hold_ticks;
extern short camera_shoulder_repeat_latch;
extern u8 runtime_state_restore_requested;
extern u8 scene_music_hold;
extern u8 D_80080AA0;

/* Handles a held button combination and restores saved settings when it triggers. */

int func_8003D92C(void);

#endif
