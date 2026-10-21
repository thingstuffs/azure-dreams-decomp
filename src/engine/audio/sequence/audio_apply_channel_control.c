#include "slus/jtbl_80057D20.h"
#include "common.h"



/* Rodata owner: the row's switch emits its jump table(s) into this object's .rodata,
 * placed at the retail address by config/slus_modules.json (assets/800.bin carve). */


void audio_apply_channel_control(u8 channel, u8 control, u32 value)
{
    S_80084960 *settings = &audio_channel_controls[channel];
    s32 refresh_notes = 0;
    s32 stopped_voices = 0;
    s32 voice_idx;
    u32 control_value;
    s32 entry_idx;
    s32 voice_status;
    s32 pending_voices;
    control_value = value;
    switch (control) {
    case 1:
        if (((u32) settings->f48) < 0x40) {
            settings->f08 = control_value & 0xFF;
            settings->f40 = ((u8) control_value) << 1;
            if ((settings->f44 != 0) && (settings->f40 != 0)) {
                settings->f38 = ((u32) settings->f40 << 2) / settings->f44;
            }
            else {
                settings->f3a = 0;
                for (voice_idx = 0; voice_idx < *(s32 *)&audio_voice_count; voice_idx++) {
                    if (audio_voice_records[voice_idx].f06 == channel) {
                        audio_update_voice_pitch(&audio_voice_records[voice_idx], 1);
                    }
                }
            }
            if (((control_value & 0xFF) == 0) || (settings->f38 == 0)) {
                settings->f3a = 0;
                for (voice_idx = 0; voice_idx < *(s32 *)&audio_voice_count; voice_idx++) {
                    if (audio_voice_records[voice_idx].f06 == channel) {
                        audio_update_voice_pitch(&audio_voice_records[voice_idx], 1);
                    }
                }
            }
        }
        else {
            settings->f08 = control_value & 0xFF;
            settings->f44 = control_value & 0xFF;
            if (((control_value & 0xFF) != 0) && (settings->f40 != 0)) {
                settings->f38 = (settings->f40 / (control_value & 0xFF)) << 1;
            }
            else {
                settings->f3a = 0;
                for (voice_idx = 0; voice_idx < *(s32 *)&audio_voice_count; voice_idx++) {
                    if (audio_voice_records[voice_idx].f06 == channel) {
                        audio_update_voice_pitch(&audio_voice_records[voice_idx], 1);
                    }
                }
            }
            if (((control_value & 0xFF) == 0) || (settings->f38 == 0)) {
                settings->f3a = 0;
                for (voice_idx = 0; voice_idx < *(s32 *)&audio_voice_count; voice_idx++) {
                    if (audio_voice_records[voice_idx].f06 == channel) {
                        audio_update_voice_pitch(&audio_voice_records[voice_idx], 1);
                    }
                }
            }
        }
        func_80055E7C(4, channel, settings->f08);
        break;

    case 2:
        if (((u32) settings->f48) < 0x40) {
            settings->f44 = (u8) control_value;
        }
        else {
            settings->f40 = (control_value & 0xFF) << 1;
        }
        break;

    case 3:
        settings->f48 = control_value & 0xFF;
        break;

    case 4:
        settings->f28 = control_value & 0xFF;
        break;

    case 5:
        settings->f50 = control_value & 0xFF;
        break;

    case 7:
        {
            settings->f0c = control_value & 0xFF;
            pending_voices = 1;
            refresh_notes = pending_voices;
            func_80055E7C(3, channel, control_value & 0xFF);
            break;
        }

    case 10:
        {
            settings->f04 = ((control_value & 0xFF) == 0) ? (1) : (control_value & 0xFF);
            pending_voices = 1;
            refresh_notes = pending_voices;
            func_80055E7C(2, channel, settings->f04);
            break;
        }

    case 11:
        {
            settings->f14 = control_value & 0xFF;
            pending_voices = 1;
            refresh_notes = pending_voices;
            func_80055E7C(5, channel, control_value & 0xFF);
            break;
        }

    case 12:
        {
            settings->f2c = control_value & 0xFF;
            pending_voices = 1;
            refresh_notes = pending_voices;
            break;
        }

    case 20:
        settings->f6c = control_value << 1;
        break;

    case 21:
        settings->f6e = control_value;
        break;

    case 22:
        settings->f68 = (control_value & 0xFF) << 4;
        settings->f64 = (control_value & 0xFF) << 4;
        settings->f6d = 0;
        settings->f5d = 1;
        break;

    case 23:
        settings->f6d = control_value;
        if (((control_value & 0xFF) != 0) && (settings->f68 != 0)) {
            settings->f70 = settings->f68 / (control_value & 0xFF);
            if (settings->f70 == 0) {
                settings->f70 = 1;
            }
        }
        break;

    case 25:
        settings->f88 = control_value << 1;
        break;

    case 26:
        settings->f8a = control_value;
        break;

    case 27:
        settings->f84 = (control_value & 0xFF) << 7;
        settings->f80 = (control_value & 0xFF) << 7;
        settings->f89 = 0;
        settings->f78 = 1;
        break;

    case 28:
        settings->f89 = control_value;
        if (((control_value & 0xFF) != 0) && (settings->f84 != 0)) {
            settings->f8c = settings->f84 / (control_value & 0xFF);
            if (settings->f8c == 0) {
                settings->f8c = 1;
            }
        }
        break;

    case 30:
        audio_master_level.f0 = control_value & 0xFF;
        audio_refresh_sequence_voice_volumes();
        break;

    case 64:
        for (entry_idx = 0; entry_idx < *(s32 *)&audio_voice_count; entry_idx++) {
            if (channel == audio_voice_records[entry_idx].f06) {
                if (((u32) (control_value & 0xFF)) < 0x40) {
                    for (voice_idx = 0; voice_idx < *(s32 *)&audio_voice_count; voice_idx++) {
                        if (((audio_voice_records[voice_idx].f06 == channel) && (audio_voice_records[voice_idx].f1d != 0))
                            && (audio_voice_records[voice_idx].f1c & 0x80)) {
                            {
                                voice_status = audio_voice_masks[voice_idx];
                                pending_voices = stopped_voices;
                                pending_voices |= voice_status;
                                stopped_voices = pending_voices;
                            }
                            do {
                                set_spu_voice_keys(0, audio_voice_masks[voice_idx]);
                                voice_status = read_selected_voice_key_state(audio_voice_masks[voice_idx]);
                            }
                            while ((voice_status != 2) && (voice_status != 0));
                            audio_voice_records[voice_idx].f1d = 0;
                            audio_voice_records[voice_idx].f1a = 0;
                        }
                    }

                    audio_voice_records[entry_idx].f1d = 0;
                }
                else {
                    audio_voice_records[entry_idx].f1d = 1;
                }
            }
        }

        if (((u32) (control_value & 0xFF)) < 0x40) {
            audio_channel_controls[channel].f18 = 0;
        }
        else {
            audio_channel_controls[channel].f18 = 1;
        }
        break;

    case 91:
        settings->f30 = control_value & 0x7F;
        break;

    case 6:
        settings->f4e = control_value;
        if ((settings->f4d != 0x14) && (settings->f4d != 0x1E)) {
            apply_tone_parameter_command(settings);
        }
        break;

    case 98:
        settings->f4c = control_value;
        break;

    case 99:
        settings->f4d = control_value;
        break;

    case 120:

    case 121:

    case 123:
        audio_reset_sequence_tracks_and_channels();
        break;

    case 126:
        settings->f98 = control_value;
        break;

    default:
        break;
    }

    {
        s32 stop_mask = stopped_voices;
        if (stop_mask) {
            set_spu_voice_keys(0, stop_mask);
        }
    }
    {
        s32 needs_refresh = refresh_notes;
        if (needs_refresh) {
            for (entry_idx = 0; entry_idx < *(s32 *)&audio_voice_count; entry_idx++) {
                if ((channel == audio_voice_records[entry_idx].f06) && (audio_voice_records[entry_idx].f1a != 0)) {
                    audio_compute_voice_stereo_volumes(&audio_voice_records[entry_idx], &audio_channel_controls[channel]);
                    sound_set_indexed_voice_volumes(entry_idx, audio_voice_records[entry_idx].f10, audio_voice_records[entry_idx].f12);
                }
            }
        }
    }
}
