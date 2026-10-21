#include "shared/sound_state.h"
#include "common.h"
#include "engine/audio.h"
#include "slus.h"

/* Canonical status-block struct (established in w_800540A8.c / w_80054C58.c /
   w_800559B4.c / w_8005440C.c). field1C added here (previously an unnamed
   2-byte pad window) since this function reads it as a signed 16-bit value. */

/* Canonical task/timer object struct (established in w_800559B4.c / w_800540A8.c
   / w_80054C58.c). */

/* Opaque scalar flag; only its address is taken (never dereferenced beyond a
   single s32 write). Padded >8 bytes to force %hi/%lo addressing (matches the
   target's lui+addiu/sw sequence rather than a $gp_rel store). */
typedef struct S_80084904 {
    /* 0x00 */ s32 v;
    /* 0x04 */ u8 pad4[8];
} S_80084904;

/* Same shape/reasoning as S_80084904. */

extern S_80084904 audio_sequence_task_mode;

/* Handles byte opcodes to arm, commit, or cancel a countdown. */
void audio_handle_stream_control_event(s32 event) {
    s32 opcode = event & 0xFF;

    switch (opcode) {
    case 0x74:
        submit_tagged_driver_byte(0, 0, 0);
        Control_CD(9, 0, 0);
        sound_playback_state.flags00 &= ~0x400;
        if (sound_playback_state.unk_18 == 0) {
            audio_sequence_task_mode.v = 1;
            sound_stream_task.unk_04 = 0;
            if (sound_playback_state.unk_10 != 0) {
                s16 countdown = (s16)select_audio_mode_attenuation(sound_playback_state.unk_1C);
                sound_stream_task.unk_08 = countdown;
                sound_stream_task.unk_0A = countdown;
                break;
            }
        }
        return;

    case 0xE4:
        if (sound_playback_state.flags04 & 0x200) {
            Control_CD(9, 0, 0);
            return;
        }
        if (sound_playback_state.flags00 & 0x400) {
            u32 cd_position = (u32)sound_get_cd_sector_position();
            sound_playback_state.unk_18 = cd_position;
            if (sound_playback_state.unk_08 >= cd_position) {
                sound_playback_state.unk_18 = sound_playback_state.unk_08;
            }
            sound_stream_task_word[0] = 2;
            sound_playback_state.unk_10 = sound_playback_state.unk_18;
            sound_playback_state.unk_14 = sound_playback_state.unk_0C;
            sound_playback_state.unk_31 = sound_playback_state.unk_30;
            sound_playback_state.unk_33 = sound_playback_state.unk_32;
            sound_playback_state.flags00 |= 0x4000;
        }
        return;

    case 0xF4:
        if (sound_playback_state.flags00 & 0x4000) {
            sound_playback_state.unk_18 = 0;
            break;
        }
        return;

    default:
        return;
    }
    activate_pending_playback();
    sound_begin_cd_playback_setup();
}
