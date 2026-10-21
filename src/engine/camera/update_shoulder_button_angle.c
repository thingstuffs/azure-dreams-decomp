#include "slus/gp_d92c_owned.h"

#include "slus/gp_d92c_owned.h"
#include "engine/camera.h"

int update_shoulder_button_angle(void)
{
    int trigger_flags;
    int held_flags;
    int flags;
    int saved_setting;
    GameWork *input_state;
    input_state = &g_game_work;
    if (runtime_dispatch_state.flags0F & 0x80) {
        return 0;
    }
    trigger_flags = ((int)input_state->pressed_buttons);
    if (trigger_flags & 0x100) {
        if (!(input_state->buttons & 0x800)) {
            camera_shoulder_repeat_latch = 1;
        }
    }
    else if (trigger_flags & 0x800) {
        if (input_state->buttons & 0x100) {
            camera_shoulder_repeat_latch = 1;
        }
        else {
            camera_shoulder_repeat_latch = 0;
            camera_shoulder_hold_ticks = 0;
            return 0;
        }
    }
    held_flags = input_state->buttons;
    if (!(held_flags & 0x100)) {
        camera_shoulder_repeat_latch = 0;
        camera_shoulder_hold_ticks = 0;
        return 0;
    }
    if (camera_shoulder_repeat_latch != 0) {
        if (held_flags & 0x800) {
            camera_shoulder_hold_ticks += animation_tick_scale;
            if (camera_shoulder_hold_ticks >= 0x169) {
                camera_shoulder_hold_ticks = 0x168;
            }
        }
        else {
            camera_shoulder_hold_ticks = 0;
        }
    }
    if ((0x78 / animation_tick_scale) < camera_shoulder_hold_ticks) {
        camera_shoulder_repeat_latch = 0;
        camera_shoulder_hold_ticks = 0;
        drain_cd_command_queue();
        while (read_sound_mode_blocking_status(4) == 0x100) {
            service_cd_command_queue();
            update_vsync_frame_id(2);
        }

        SD_Call(0x74);
        while (read_sound_mode_blocking_status(4) != 0) {
            service_cd_command_queue();
            update_vsync_frame_id(2);
        }

        drain_cd_command_queue();
        request_scene_dispatch_state(3);
        {
            saved_setting = saved_cd_playback_volume_scale;
            flags = runtime_dispatch_state.field_0;
            runtime_state_restore_requested = 0;
            scene_music_hold = 0;
            D_80080AA0 = 0;
            runtime_dispatch_state.field_0 = flags & ~2;
            sound_set_cd_playback_volume_scale(saved_setting);
        }
        sound_set_sequence_volume_scale(saved_sequence_volume_scale);
        sound_set_voice_gain_scale(saved_voice_gain_scale);
        SD_Call(0x7F);
        reset_game_state_preserving_session_fields();
        animation_tick_scale = 2;
        return 1;
    }
    return 0;
}

short camera_shoulder_hold_ticks = 0;
short camera_shoulder_repeat_latch = 0;
