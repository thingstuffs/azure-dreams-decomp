#include "shared/sound_state.h"
#include "common.h"

#include "common.h"




extern void update_audio_ramp(SoundTask *ramp);
extern void check_cd_stream_end(void);
extern void update_cd_stream_flags(void);
extern void audio_handle_stream_control_event(s32 event);

/* Updates the CD cue task and commits the countdown when its ramp completes. */
void func_800544A4(void) {
    if (D_800847D0.flags04 & 0x200) {
        update_cd_stream_flags();
    }

    if (D_800847D0.flags00 & 0x400) {
        if (D_800847D0.flags00 & 0x4000) {
            SoundTask *task = &D_80084858;

            update_audio_ramp(task);
            if (task->unk_0C == 3) {
                audio_handle_stream_control_event(0x74);
            }
        } else {
            check_cd_stream_end();
        }
    }
}
