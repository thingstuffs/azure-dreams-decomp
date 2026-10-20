#include "common.h"

extern void reset_audio_command_state(void);
extern void audio_load_sound_effect_bank(s32 sound_id);
extern s16 SD_Call(s32 sequence_id);

/* tw_sd_se_ld_call: prepare sound loading and process the nonzero sound and sequence IDs. */
s32 tw_sd_se_ld_call(s32 sound_id, s32 sequence_id) {
    reset_audio_command_state();
    if (sound_id != 0) {
        audio_load_sound_effect_bank((s16)sound_id);
    }
    if (sequence_id != 0) {
        SD_Call(sequence_id & 0xFFFF);
    }
    return 1;
}
