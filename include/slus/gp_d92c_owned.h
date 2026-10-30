#ifndef SLUS_GP_D92C_OWNED_H
#define SLUS_GP_D92C_OWNED_H

/* Present C interface; historical filename and TU boundary remain inferred. */
#include "shared/runtime_dispatch.h"
#include "common.h"
#include "shared/game_work.h"

extern u8 animation_tick_scale;
extern short camera_shoulder_hold_ticks;
extern short camera_shoulder_repeat_latch;
extern short saved_cd_playback_volume_scale;
extern short saved_sequence_volume_scale;
extern short saved_voice_gain_scale;
extern u8 runtime_state_restore_requested;
extern u8 scene_music_hold;
extern u8 D_80080AA0;

extern void drain_cd_command_queue(void);
extern int read_sound_mode_blocking_status(int);
extern void service_cd_command_queue(void);
extern s32 update_vsync_frame_id(s32 id_mode);
extern void func_80044618(int);
extern short SD_Call(int a0);
extern void request_scene_dispatch_state(int);
extern void sound_set_cd_playback_volume_scale(short saved_setting);
extern void sound_set_sequence_volume_scale(short);
extern void sound_set_voice_gain_scale(short a0);
extern void reset_game_state_preserving_session_fields(void);

/* Handles a held button combination and restores saved settings when it triggers. */

int func_8003D92C(void);

#endif
