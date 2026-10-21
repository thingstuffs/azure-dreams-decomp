#include "shared/sound_state.h"
#include "common.h"
#include "engine/audio.h"

/* Updates the CD cue task and commits the countdown when its ramp completes. */
void update_cd_stream_ramp_and_completion(void) {
    if (sound_playback_state.flags04 & 0x200) {
        update_cd_stream_flags();
    }

    if (sound_playback_state.flags00 & 0x400) {
        if (sound_playback_state.flags00 & 0x4000) {
            SoundTask *task = &sound_stream_task;

            update_audio_ramp(task);
            if (task->unk_0C == 3) {
                audio_handle_stream_control_event(0x74);
            }
        } else {
            check_cd_stream_end();
        }
    }
}
