#include "common.h"
#include "engine/audio.h"

extern int audio_pending_channel_flags_alias[3]; /* size > 8 to force %hi/%lo addressing (see gp-vs-hilo notes) */

/* Reactivates a pending locked channel and updates audio tasks. */
void service_audio_channels(void)
{
    if (audio_pending_channel_flags_alias[0] & 0xFF000000) {
        process_first_pending_sound_channel();
    }
    update_cd_stream_ramp_and_completion();
    service_audio_events();
}
