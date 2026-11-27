#include "common.h"
#include "slus/audio_voice_data.h"
#include "engine/audio/sequence.h"
#include "engine/audio/spu.h"

/* Populates the global descriptor from a table entry and source fields, then processes it. */
void sound_apply_indexed_voice_envelope(s32 table_index, SoundVoiceRecord *source) {
    SpuVoiceAttr_ *descriptor = &audio_voice_request;
    descriptor->mask = 0x60100;
    audio_voice_request.voice = audio_voice_masks[table_index];
    descriptor->adsr1 = source->adsr1;
    descriptor->adsr2 = source->adsr2;
    descriptor->a_mode = source->attack_mode;
    apply_spu_voice_attributes(descriptor);
}
