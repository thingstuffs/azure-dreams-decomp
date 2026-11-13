#include "common.h"
#include "slus/audio_voice_data.h"
#include "engine/audio/sequence.h"

/* D_80085458[64]: stride 0x78 table; only fields f06 (dispatch index), f10, f12
   (params forwarded to sound_set_indexed_voice_volumes) are touched by this function. */
typedef struct S_800564A8_85458 {
    /* 0x00 */ u8 pad00[6];
    /* 0x06 */ u16 f06;
    /* 0x08 */ u8 pad08[8];
    /* 0x10 */ u16 f10;
    /* 0x12 */ u16 f12;
    /* 0x14 */ u8 pad14[0x78 - 0x14];
} S_800564A8_85458;

/* Pass the selected shared audio channel control to the voice volume updater. */
extern S_800564A8_85458 audio_voice_records[24];
extern AudioChannelControl audio_channel_controls[16];

extern void audio_compute_voice_stereo_volumes(S_800564A8_85458 *voice_arg, AudioChannelControl *sound_params);

/* Process each entry with a valid dispatch index using its dispatch record and parameters. */
void audio_refresh_sequence_voice_volumes(void) {
    s32 entry_index;

    for (entry_index = 0; entry_index < audio_voice_count[0]; entry_index++) {
        if ((u16)audio_voice_records[entry_index].f06 < 0x10) {
            audio_compute_voice_stereo_volumes(&audio_voice_records[entry_index], &audio_channel_controls[audio_voice_records[entry_index].f06]);
            sound_set_indexed_voice_volumes(entry_index, audio_voice_records[entry_index].f10, audio_voice_records[entry_index].f12);
        }
    }
}
