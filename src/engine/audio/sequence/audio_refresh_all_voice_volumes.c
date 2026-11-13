#include "common.h"
#include "slus/audio_voice_data.h"
#include "engine/audio/sequence.h"

/* D_80085458: struct array, stride 0x78 (120) bytes; only fields touched here. */
typedef struct S_80085458 {
    /* 0x00 */ u8 pad00[6];
    /* 0x06 */ u16 f06;
    /* 0x08 */ u8 pad08[8];
    /* 0x10 */ u16 f10;
    /* 0x12 */ u16 f12;
    /* 0x14 */ u8 pad14[0x78 - 0x14];
} S_80085458;

/* Select the shared audio channel control using the voice channel index. */
extern S_80085458 audio_voice_records[24];
extern AudioChannelControl audio_channel_controls[16];

extern void audio_compute_voice_stereo_volumes(S_80085458 *a0, AudioChannelControl *a1);

/* Dispatch each active entry with its matching slot, then its field pair with its index. */
void audio_refresh_all_voice_volumes(void)
{
    s32 entry_index;

    for (entry_index = 0; entry_index < audio_voice_count[0]; entry_index++) {
        S_80085458 *entry = &audio_voice_records[entry_index];
        audio_compute_voice_stereo_volumes(entry, &audio_channel_controls[entry->f06]);
        sound_set_indexed_voice_volumes(entry_index, entry->f10, entry->f12);
    }
}
