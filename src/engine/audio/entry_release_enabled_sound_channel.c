#include "shared/sound_state.h"
#include "common.h"




extern void handle_audio_status_code(s32 code);
extern void release_enabled_sound_channel(s16 index);

/* Releases the selected channel and sets its secondary status flag. */
void release_sound_channel_and_mark_pending(s16 channel)
{
    if ((channel << 16) == 0 && (sound_playback_state.flags00 & 0x100)) {
        handle_audio_status_code(0x71);
    }
    release_enabled_sound_channel(channel);
    sound_playback_state.flags04 |= 0x01000000 << channel;
}
