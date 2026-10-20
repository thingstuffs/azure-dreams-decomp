#include "shared/sound_state.h"
#include "common.h"





extern void handle_audio_status_code(s32 a0);
extern void start_pending_selection(void);
extern void set_sound_task_priority(s32 a0, SoundTask *a1);

/* Dispatches a status transition or queues a packed selection for playback. */
void dispatch_audio_command(s32 code)
{
    s32 packed_code = code;

    code &= 0xF000;
    switch (code) {
    case 0:
    case 0x8000:
    case 0x9000:
    {
        SoundPlaybackState *state = &sound_playback_state;
        s32 low_byte = packed_code & 0xFF;

        state->unk_26 = (s16)low_byte;
        code = packed_code & 0xF000;
        if (code != 0) {
            state->unk_26 = (s16)(low_byte | code);
        }
        if (sound_playback_state.flags00 & 0x100) {
            set_sound_task_priority(0xB1, &sound_sequence_task);
            return;
        }
    }
        start_pending_selection();
        return;
    case 0x1000:
        code = 0x71;
        break;
    case 0x2000:
        code = 0xE1;
        break;
    case 0x4000:
        code = 0xF1;
        break;
    default:
        return;
    }
    handle_audio_status_code(code);
}
