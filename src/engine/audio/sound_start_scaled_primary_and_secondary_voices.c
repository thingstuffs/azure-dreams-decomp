#include "common.h"
#include "shared/sound_volume.h"
#include "engine/audio.h"
#include "engine/entity.h"

extern void audio_stop_matching_effect_voices(s32 packed_key, s32 packed_channel);
extern s32 start_sound_effect_program_voices(s32 a0, void *a1, u16 a2, u16 a3, s32 a4);

extern u16 primary_voice_volume_scale_alias[8];   /* size>8 forces %hi/%lo addressing */

/* Scales D_800847EE's level by volume scale [0] and starts the voices with a primary and an optional secondary gain. */
void sound_start_scaled_primary_and_secondary_voices(s32 target_id, void *target_data)
{
    s32 scale_value;
    s32 primary_amount;
    s32 secondary_amount;

    audio_stop_matching_effect_voices(target_id, (s32)target_data);

    scale_value = primary_voice_volume_scale_alias[0] * g_volume_scale[0];
    primary_amount = clamp_sound_value_to_seven_bits((s16)(scale_value / 32767));

    scale_value = read_capped_audio_meter();
    secondary_amount = (scale_value * (g_volume_scale[0] + g_volume_scale[0])) / 32767;

    if (secondary_amount == 0) {
        start_sound_effect_program_voices(target_id, target_data, primary_amount, primary_amount, 0);
    } else {
        primary_amount -= secondary_amount;
        start_sound_effect_program_voices(target_id, target_data, primary_amount, primary_amount, 0);
        start_sound_effect_program_voices(target_id, target_data, secondary_amount, secondary_amount, 1);
    }
}
