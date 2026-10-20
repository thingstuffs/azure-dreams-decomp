#include "common.h"

/* Inferred layout for D_80084918, shared with sibling functions in this
 * global's family (audio_update_voice_tremolo, audio_update_voice_pitch, sound_set_indexed_voice_volumes,
 * sound_apply_indexed_voice_envelope, start_channel_note). Only the fields this function touches
 * are given exact offsets/types here. */
typedef struct S_80084918 {
    /* 0x00 */ s32 field_0x00;
    /* 0x04 */ s32 field_0x04;
    u8 pad_0x08[0x24 - 0x08];
    /* 0x24 */ s32 field_0x24;
    u8 pad_0x28[0x3A - 0x28];
    /* 0x3A */ s16 field_0x3A;
    /* 0x3C */ s16 field_0x3C;
} S_80084918;

extern S_80084918 audio_voice_request;
extern s32 audio_voice_masks[];

extern void func_8005F134(S_80084918 *descriptor);

/* Builds and submits a request using the indexed table value. */
void sound_reset_indexed_voice_envelope(s32 request_index) {
    s32 request_value;

    audio_voice_request.field_0x04 = 0x60100;
    request_value = audio_voice_masks[request_index];
    audio_voice_request.field_0x3A = 0;
    audio_voice_request.field_0x3C = 0;
    audio_voice_request.field_0x24 = 5;
    audio_voice_request.field_0x00 = request_value;
    func_8005F134(&audio_voice_request);
}
