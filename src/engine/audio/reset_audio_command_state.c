#include "shared/sound_state.h"
#include "common.h"
#include "engine/audio.h"
#include "slus.h"

/*
 * Resets the audio command state and task object, then clears playback status fields.
 *
 * callee: task/timer-like initializer, already matched in src/code.c
 *
 * Sibling struct for sound_playback_state: fields cleared here are a subset of a larger object;
 * layout inferred purely from the offsets this function touches.
 */
void reset_audio_command_state(void) {
    set_cd_ext_reverb_or_mix(0, 0, 0);
    initialize_audio_ramp_defaults(&sound_stream_task);

    sound_playback_state.stream_start_sector = 0;
    sound_playback_state.stream_end_sector = 0;
    sound_playback_state.stream_xa_channel = 0;
    sound_playback_state.stream_xa_file = 0;
    sound_playback_state.pending_start_sector = 0;
    sound_playback_state.pending_end_sector = 0;
    sound_playback_state.pending_xa_channel = 0;
    sound_playback_state.pending_xa_file = 0;
    sound_playback_state.paused_sector = 0;
}
