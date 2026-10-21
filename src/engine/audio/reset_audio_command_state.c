#include "shared/sound_state.h"
#include "common.h"
#include "engine/audio.h"
#include "slus.h"

/* callee: task/timer-like initializer, already matched in src/code.c */

/* Sibling struct for D_800847D0: fields cleared here are a subset of a larger
   object; layout inferred purely from the offsets this function touches. */


/* Resets the audio command state and task object, then clears playback status fields. */
void reset_audio_command_state(void) {
    submit_tagged_driver_byte(0, 0, 0);
    initialize_audio_ramp_defaults(&sound_stream_task);

    ((s32)sound_playback_state.unk_08) = 0;
    ((s32)sound_playback_state.unk_0C) = 0;
    sound_playback_state.unk_30 = 0;
    sound_playback_state.unk_32 = 0;
    ((s32)sound_playback_state.unk_10) = 0;
    ((s32)sound_playback_state.unk_14) = 0;
    sound_playback_state.unk_31 = 0;
    sound_playback_state.unk_33 = 0;
    ((s32)sound_playback_state.unk_18) = 0;
}
