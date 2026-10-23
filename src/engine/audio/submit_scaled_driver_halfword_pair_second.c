#include "shared/sound_state.h"
#include "common.h"
#include "shared/sound_volume.h"
#include "engine/audio.h"

/*
 * When status flag 0x400 is set: sound_stream_task's level, scaled by volume scale [2], goes to
 * submit_scaled_driver_halfword_pair (mode 0).
 *
 * Canonical status block shared across the sound_playback_state family (w_800540A8.c,
 * w_80054C58.c, w_8005405C.c, w_800559B4.c). Only flags1 is touched here.
 *
 * Canonical "task/timer object" struct established in w_800559B4.c. field0 is a callback pointer
 * (set to apply_scaled_cd_stream_volume there); field8/field10 are the two s16 fields this
 * function reads.
 */
void apply_scaled_cd_stream_volume(void) {
    s16 level;
    s32 scaled;

    if (sound_playback_state.flags00 & 0x400) {
        SoundTask *task = &sound_stream_task;

        level = (task->unk_08 * g_volume_scale[2]) / 32767;
        scaled = level * task->unk_10;
        level = scaled / 128;
        submit_scaled_driver_halfword_pair(0, level, level);
    }
}
