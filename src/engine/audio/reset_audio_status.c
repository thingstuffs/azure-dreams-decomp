#include "shared/sound_state.h"
#include "common.h"
#include "shared/sound_volume.h"

/* Canonical "task/timer object" struct shared with func_80055990's own SoundTask
   (src/code.c) and w_800540A8.c's SoundTask / w_80054C58.c's SoundTask: field0 is
   revealed here as a function pointer (this function stores a callback address into it),
   and the two 4-byte pad windows are each a pair of s16 fields. */

/* Same layout as SoundTask (SoundTask family), independently named per its own
   global address per convention. */

/* Extends the SoundPlaybackState view already established in w_800540A8.c / w_80054C58.c /
   w_8005405C.c (flags1@0x0, flags2@0x4, field8/fieldC/field10/field14@0x8/0xC/0x10/0x14,
   field30..33@0x30..0x33) with the additional fields this function touches in the
   0x18-0x29 window. */

extern s32 audio_stream_request_count[];

extern void initialize_audio_ramp_defaults(void *a0);

/* Resets global status and initializes two task objects with callbacks and defaults. */
void reset_audio_status(void) {
    sound_playback_state.flags00 = 0;
    sound_playback_state.flags04 = 0;
    sound_playback_state.flags00 = 0x10;
    sound_playback_state.unk_1E = 0x5A;
    sound_playback_state.unk_26 = -1;

    sound_playback_state.unk_08 = 0;
    sound_playback_state.unk_0C = 0;
    sound_playback_state.unk_30 = 0;
    sound_playback_state.unk_32 = 0;
    sound_playback_state.unk_10 = 0;
    sound_playback_state.unk_14 = 0;
    sound_playback_state.unk_31 = 0;
    sound_playback_state.unk_33 = 0;
    sound_playback_state.unk_18 = 0;
    sound_playback_state.unk_22 = 0;
    sound_playback_state.unk_20 = 0;

    g_volume_scale[0] = 0x7FFF;
    g_volume_scale[1] = 0x7FFF;
    g_volume_scale[2] = 0x7FFF;

    audio_stream_request_count[0] = 0;
    initialize_audio_ramp_defaults(&sound_sequence_task);

    initialize_audio_ramp_defaults(&sound_stream_task);

    sound_sequence_task.callback = apply_scaled_sound_slot_volume;
    sound_sequence_task.unk_08 = 0x64;
    sound_sequence_task.unk_0A = 0x64;
    sound_sequence_task.unk_12 = 0x50;
    sound_sequence_task.unk_14 = 2;

    sound_stream_task.callback = apply_scaled_cd_stream_volume;
    sound_stream_task.unk_08 = 0x7F;
    sound_stream_task.unk_0A = 0x7F;
    sound_stream_task.unk_14 = 0x14;
    sound_stream_task.unk_12 = 0;

    sound_playback_state.unk_28 = 0xC8;
}
