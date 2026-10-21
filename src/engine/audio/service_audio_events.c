#include "shared/sound_state.h"
#include "common.h"
#include "engine/audio.h"
#include "engine/audio/sequence.h"

/* Sibling struct (matches src/w_80054C58.c's SoundPlaybackState exactly for the
 * fields touched here): flags1 at 0x0, flags2 at 0x4. */

/* Opaque state-block struct: only its address is taken here (never
 * dereferenced), but sibling functions in this wave show a function-pointer
 * field at 0x0, an s32 flag/counter at 0x4, and an s16 timer at 0x8. Declared
 * >8 bytes to force %hi/%lo addressing. */

/* Handles flag-triggered events and status checks, then dispatches the state block. */
void service_audio_events(void) {
    if (sound_playback_state.flags04 & 0x2) {
        start_pending_selection();
    }

    if (sound_playback_state.flags00 & 0x100) {
        if (get_sequence_play_state() == 3 || update_audio_fade(&sound_sequence_task) == -1) {
            handle_audio_status_code(0x71);
        }
    }

    update_audio_ramp(&sound_sequence_task);
}
