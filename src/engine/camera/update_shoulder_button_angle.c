#include "slus/gp_d92c_owned.h"

#include "slus/gp_d92c_owned.h"

int update_shoulder_button_angle(void)
{
    int trigger_flags;
    int held_flags;
    int flags;
    int saved_setting;
    GameWork *input_state;
    input_state = &g_game_work;
    if (D_80082E60.flags0F & 0x80) {
        return 0;
    }
    trigger_flags = ((int)input_state->unk_010);
    if (trigger_flags & 0x100) {
        if (!(input_state->buttons & 0x800)) {
            D_80080ABE = 1;
        }
    }
    else if (trigger_flags & 0x800) {
        if (input_state->buttons & 0x100) {
            D_80080ABE = 1;
        }
        else {
            D_80080ABE = 0;
            D_80080ABC = 0;
            return 0;
        }
    }
    held_flags = input_state->buttons;
    if (!(held_flags & 0x100)) {
        D_80080ABE = 0;
        D_80080ABC = 0;
        return 0;
    }
    if (D_80080ABE != 0) {
        if (held_flags & 0x800) {
            D_80080ABC += D_80080A84;
            if (D_80080ABC >= 0x169) {
                D_80080ABC = 0x168;
            }
        }
        else {
            D_80080ABC = 0;
        }
    }
    if ((0x78 / D_80080A84) < D_80080ABC) {
        D_80080ABE = 0;
        D_80080ABC = 0;
        drain_cd_command_queue();
        while (func_80053EF0(4) == 0x100) {
            func_8003E758();
            update_vsync_frame_id(2);
        }

        SD_Call(0x74);
        while (func_80053EF0(4) != 0) {
            func_8003E758();
            update_vsync_frame_id(2);
        }

        drain_cd_command_queue();
        func_80040AA0(3);
        {
            saved_setting = D_80080A94;
            flags = D_80082E60.field_0;
            D_80080A8A = 0;
            D_80080A88 = 0;
            D_80080AA0 = 0;
            D_80082E60.field_0 = flags & ~2;
            sound_set_cd_playback_volume_scale(saved_setting);
        }
        sound_set_sequence_volume_scale(D_80080A98);
        sound_set_voice_gain_scale(D_80080A9C);
        SD_Call(0x7F);
        reset_game_state_preserving_session_fields();
        D_80080A84 = 2;
        return 1;
    }
    return 0;
}

short D_80080ABC = 0;
short D_80080ABE = 0;
