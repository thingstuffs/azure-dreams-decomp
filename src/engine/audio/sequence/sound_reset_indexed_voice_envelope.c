#include "common.h"
#include "engine/audio/sequence.h"
#include "engine/audio/spu.h"

/* Inferred layout for D_80084918, shared with sibling functions in this
 * global's family (audio_update_voice_tremolo, audio_update_voice_pitch, sound_set_indexed_voice_volumes,
 * sound_apply_indexed_voice_envelope, start_channel_note). Only the fields this function touches
 * are given exact offsets/types here. */


extern SpuVoiceAttr_ audio_voice_request;
extern s32 audio_voice_masks[];

/* Builds and submits a request using the indexed table value. */
void sound_reset_indexed_voice_envelope(s32 request_index) {
    s32 request_value;

    audio_voice_request.mask = 0x60100;
    request_value = audio_voice_masks[request_index];
    audio_voice_request.adsr1 = 0;
    audio_voice_request.adsr2 = 0;
    audio_voice_request.a_mode = 5;
    audio_voice_request.voice = request_value;
    apply_spu_voice_attributes(&audio_voice_request);
}
