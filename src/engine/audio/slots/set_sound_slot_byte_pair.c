#include "shared/sound_state.h"
#include "common.h"
#include "shared/sound_volume.h"
#include "engine/audio/sequence.h"
#include "engine/audio/slots.h"
#include "engine/entity.h"

/*
 * When playback flag 0x100 is set, scales the sequence task value by g_volume_scale[1] and its
 * task multiplier, clamps to seven bits, and writes the same volume to both slot channels.
 */
void apply_scaled_sound_slot_volume(void)
{
    s32 scale_product;
    s32 scaled_value;
    s16 channel_value;

    if (sound_playback_state.flags00 & 0x100) {
        scale_product = sound_sequence_task.unk_08 * g_volume_scale[1];
        scaled_value = (s16) (scale_product / 32767);
        scaled_value = scaled_value * sound_sequence_task.unk_10;
        channel_value = clamp_sound_value_to_seven_bits((s16) (scaled_value / 128));
        set_sound_slot_byte_pair(sound_playback_state.unk_22, channel_value, channel_value);
    }
}
