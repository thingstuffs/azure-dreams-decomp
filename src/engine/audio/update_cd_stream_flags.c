#include "shared/sound_state.h"
#include "common.h"

#include "common.h"
#include "engine/audio.h"
#include "slus.h"

/* Canonical status block shared across the D_800847D0 family (established in
   w_80054E00.c / w_800540A8.c / w_80054C58.c / w_800559B4.c). */

/* When subsystem bit 4 is set, clears flag 0x200 and commits or arms the countdown. */
void update_cd_stream_flags(void) {
    if (get_cd_flags_with_conditional_bit() & 4) {
        sound_playback_state.flags04 &= ~0x200;
        if (sound_playback_state.unk_10 != 0) {
            audio_handle_stream_control_event(0x74);
            return;
        }
        if (!(sound_playback_state.flags00 & 0x4000)) {
            sound_playback_state.flags00 |= 0x400;
            apply_scaled_cd_stream_volume();
            submit_tagged_driver_byte(0, 0, 1);
        }
    }
}
